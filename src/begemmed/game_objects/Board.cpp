#include "Board.h"

#include "src/begemmed/BegemmedSound.h"
#include "src/begemmed/GameManager.h"
#include "src/engine/input/InputHandler.h"
#include "src/engine/sound/SoundManager.h"

#include <chrono>

using namespace BegemmedSound;

Board::Board(Vec2f pos, int width, int height) : GameObject(pos), _width(width), _height(height) {
  for (int i = 0; i < _width; ++i) {
    std::vector<Gem*> new_column;
    _board_gems.push_back(new_column);
  }
  _generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

  while (true) {
    fillBoard(true);
    std::vector<std::vector<Vec2i>> matches {};
    // Break any already made matches
    do {
      matches = searchMatches();
      if (matches.size() > 0) {
        breakGems(matches, true);
      }
    } while (matches.size() > 0);
    // Make sure there's a possible match
    if (searchHint(true) != Vec2i(-1, -1)) {
      break;
    }
    breakAllGems(true);
  }
}

void Board::update(int delta_time) {
  if (!_game_is_over) {
    // Release previous frame's hovering
    if (_hovered_gem != nullptr && _hovered_gem->getState() == Gem::State::Hovered) {
      _hovered_gem->setState(Gem::State::Default);
    }

    // Check if mouse was released if needed to hover gems
    if (_need_release_to_hover) {
      bool mouse_release = InputHandler::instance()->getMouseLeftRelease();
      bool mouse_press   = InputHandler::instance()->getMouseLeftPress();
      if (mouse_release) {
        _need_release_to_hover = false;
      } else if (mouse_press && _state != State::Default) {
        _need_release_to_hover = true;
      }
    }

    // Main Handling
    switch (_state) {
      case State::Default: handleInputDefault(); break;
      case State::Swapping: handleInputSwapping(); break;
      case State::Reverting: handleInputReverting(); break;
      case State::MovingGems: handleInputMovingGems(); break;
    }
  }

  // Update each gem and check if there are any moving gems
  _moving_gems = false;
  for (const auto& column: _board_gems) {
    for (const auto& gem: column) {
      gem->update(delta_time);
      if (gem->isMoving()) {
        _moving_gems = true;
      }
    }
  }

  // Manage gems that are being destroyed
  for (size_t ii = 0; ii < _being_destroyed_gems.size(); ++ii) {
    _being_destroyed_gems.at(ii)->update(delta_time);
    if (_being_destroyed_gems.at(ii)->getState() == Gem::State::ToDestroy) {
      delete _being_destroyed_gems.at(ii);
      _being_destroyed_gems.erase(_being_destroyed_gems.begin() + ii);
    }
  }
}

void Board::render() const {
  for (const auto& column: _board_gems) {
    for (const auto& gem: column) {
      gem->render();
    }
  }
  for (const auto& gem: _being_destroyed_gems) {
    gem->render();
  }
}

Vec2i Board::searchHint(bool instant) {
  const Vec2i no_gem {-1, -1};
  Vec2i hinted_pos {-1, -1};

  // Check if a swap results in a match
  auto checkSwap = [this, &hinted_pos, &instant](Vec2i pos1, Vec2i pos2) {
    swapGems(pos1, pos2);
    auto matches = searchMatches();
    swapGems(pos1, pos2);
    if (matches.size() > 0) {
      if (!instant && _hinted_gem != _board_gems.at(pos1.x).at(pos1.y)) {
        _hinted_gem = _board_gems.at(pos1.x).at(pos1.y);
        _hinted_gem->setAnimation(Gem::cAnimFlashing, true);
      }
      hinted_pos = pos1;
    }
  };

  // Check Horizontal Swaps
  for (int x = 0; x < _width - 1; ++x) {
    for (int y = 0; y < _height; ++y) {
      checkSwap({x, y}, {x + 1, y});
      if (hinted_pos != no_gem) {
        return hinted_pos;
      }
    }
  }
  // Check Vertical Swaps
  for (int x = 0; x < _width; ++x) {
    for (int y = 0; y < _height - 1; ++y) {
      checkSwap({x, y}, {x, y + 1});
      if (hinted_pos != no_gem) {
        return hinted_pos;
      }
    }
  }
  return no_gem;
}

// Sets all gems in for destruction.
void Board::breakAllGems(bool instant, bool game_is_over) {
  _game_is_over = game_is_over;
  for (int i = static_cast<int>(_board_gems.size()) - 1; i >= 0; --i) {
    for (int ii = static_cast<int>(_board_gems.at(i).size()) - 1; ii >= 0; --ii) {
      destroyGem(i, ii, instant);
    }
  }
}

Board::~Board() {
  for (const auto& column: _board_gems) {
    for (const auto& gem: column) {
      delete gem;
    }
  }
  for (const auto& gem: _being_destroyed_gems) {
    delete gem;
  }
}

std::vector<Gem*> Board::addGems(int x, int amount) {
  std::uniform_int_distribution<int> distribution(0, Gem::cNumberOfColors - 1);
  std::vector<Gem*> new_gems;

  for (int i = 0; i < amount; ++i) {
    Gem::Color color = Gem::Color(distribution(_generator));
    int y            = (_height - _board_gems.at(x).size() - 1);
    Vec2f pos        = _pos + Vec2f(x * Gem::cSize.x, y * Gem::cSize.y);
    Gem* new_gem     = new Gem(pos, color);
    _board_gems.at(x).push_back(new_gem);
    new_gems.push_back(new_gem);
  }
  return new_gems;
}

void Board::fillBoard(bool instant) {
  // Creates gems in their correct places
  for (size_t x = 0; x < _board_gems.size(); ++x) {
    int gap_height  = _height - _board_gems.at(x).size();
    auto added_gems = addGems(x, gap_height);
    if (instant) {
      continue;
    }
    for (const auto& gem: added_gems) {
      // Move gems from one slot above to give some time before possible next match
      gem->moveFrom(Vec2f(0, (-gap_height - 1) * Gem::cSize.y));
    }
  }
}

void Board::destroyGem(int x, int y, bool instant) {
  std::vector<Gem*>& column = _board_gems.at(x);

  if (instant) {
    delete column.at(y);
  } else {
    _being_destroyed_gems.push_back(column.at(y));
    column.at(y)->setState(Gem::State::Breaking);
  }
  column.erase(column.begin() + y);

  // Move every Gem above
  for (size_t ii = y; ii < column.size(); ++ii) {
    Gem* gem = column.at(ii);
    if (instant) {
      column.at(ii)->setPos(gem->getPos() + Vec2f(0, Gem::cSize.y));
    } else {
      gem->moveTo(Vec2f(0, Gem::cSize.y));
    }
  }
}

int Board::calculateScore(int amount) const {
  return (amount - 2) * 50 * (1 + 0.5 * (_match_cycle - 1));
}

void Board::breakGems(std::vector<std::vector<Vec2i>> gems_pos, bool instant) {
  std::vector<Vec2i> to_break {};
  for (const auto& groups: gems_pos) {
    if (!instant) {
      GameManager::instance()->addScore(calculateScore(groups.size()));
    }
    std::copy(groups.begin(), groups.end(), std::back_inserter(to_break));
  }

  // Erase possible duplicate gems from split matches
  std::sort(to_break.begin(), to_break.end(), [](Vec2i a, Vec2i b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  });
  auto last = std::unique(to_break.begin(), to_break.end());
  to_break.erase(last, to_break.end());

  // Play Sound
  if (!instant) {
    switch (_match_cycle) {
      case 1: SoundManager::instance()->playSFX(cSoundBreak); break;
      case 2: SoundManager::instance()->playSFX(cSoundBreak2); break;
      case 3: SoundManager::instance()->playSFX(cSoundBreak3); break;
      default: SoundManager::instance()->playSFX(cSoundBreak4); break;
    }
  }

  // Destroy gems
  std::sort(to_break.begin(), to_break.end(), [](Vec2i a, Vec2i b) {
    return a.y > b.y;
  });
  for (const auto& pos: to_break) {
    destroyGem(pos.x, pos.y, instant);
  }

  // Fill board
  fillBoard(instant);
}

std::vector<std::vector<Vec2i>> Board::searchMatches() {
  std::vector<std::vector<Vec2i>> matches {};
  std::vector<Vec2i> current_set {};

  // Check if current set is a match
  auto checkSet = [&current_set, &matches]() {
    if (current_set.size() >= 3) {
      matches.push_back(current_set);
    }
    current_set.clear();
  };

  // Check if current gem matches the ones from current set
  auto checkGem = [this, &current_set, &checkSet](int x, int y) {
    Gem* gem = _board_gems.at(x).at(y);
    for (const auto& pos: current_set) {
      Gem* otherGem = _board_gems.at(pos.x).at(pos.y);
      if (gem->getColor() != otherGem->getColor()) {
        checkSet();
        break;
      }
    }
    current_set.push_back({x, y});
  };

  // Do one pass for every line and every column
  // Can return duplicate gems if they are in
  // both an horizontal and vertical match.
  for (int x = 0; x < _width; ++x) {
    for (int y = 0; y < _height; ++y) {
      checkGem(x, y);
    }
    checkSet();
  }
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      checkGem(x, y);
    }
    checkSet();
  }
  return matches;
}

Vec2f Board::matrixToRealPos(Vec2i mat_pos) const {
  return _pos + Vec2i(mat_pos.x * Gem::cSize.x, (_height - mat_pos.y - 1) * Gem::cSize.y);
}

void Board::resetHeldGem() {
  _held_pos          = {-1, -1};
  _held_gem          = nullptr;
  _unhold_on_release = false;
}

void Board::resetSwapGems() {
  resetHeldGem();
  _swapped_pos = {-1, -1};
}

void Board::swapGems(Vec2i pos1, Vec2i pos2) {
  Gem* gem1 = _board_gems.at(pos1.x).at(pos1.y);
  Gem* gem2 = _board_gems.at(pos2.x).at(pos2.y);

  _board_gems.at(pos2.x).at(pos2.y) = gem1;
  _board_gems.at(pos1.x).at(pos1.y) = gem2;

  Vec2f real_pos2 = matrixToRealPos(pos2);
  Vec2f real_pos1 = matrixToRealPos(pos1);
  gem2->moveTo(real_pos1 - real_pos2);
  gem1->moveTo(real_pos2 - real_pos1);
}

void Board::handleInputDefault() {
  // Is mouse over any gem

  Vec2i gem_pos = Vec2i(
    floor((InputHandler::instance()->getMouseX() - _pos.x) / Gem::cSize.x),
    floor(_height - (InputHandler::instance()->getMouseY() - _pos.y) / Gem::cSize.y)
  );
  bool is_hovering_gem = gem_pos.x >= 0 && gem_pos.x < _width && gem_pos.y >= 0 && gem_pos.y < _height;

  bool mouse_press = InputHandler::instance()->getMouseLeftPress();

  // No gem is being hovered
  if (!is_hovering_gem) {
    // Stop holding gem if clicked outside of Board
    if (mouse_press && _held_gem != nullptr) {
      _held_gem->setState(Gem::State::Default);
      resetHeldGem();
    }
    return;
  }

  // Release hinted gem as soon as board is hovered
  if (_hinted_gem != nullptr) {
    _hinted_gem->setAnimation(Gem::cAnimDefault, false);
    _hinted_gem = nullptr;
  }

  bool mouse_release = InputHandler::instance()->getMouseLeftRelease();
  bool mouse_hold    = InputHandler::instance()->getMouseLeft();

  Gem* gem = _board_gems.at(gem_pos.x).at(gem_pos.y);

  // Highlight gem if:
  // - Gem is not being held on
  // - A swap wasn't made before mouse was released
  // - Mouse is not being held (but do not stop hovering in a press frame)
  if (gem != _held_gem && !_need_release_to_hover && (!mouse_hold || mouse_press)) {
    _hovered_gem = gem;
    _hovered_gem->setState(Gem::State::Hovered);
  }

  // Release hold if mouse is released after pressing held gem
  if (_unhold_on_release && mouse_release) {
    _hovered_gem = gem;
    _hovered_gem->setState(Gem::State::Hovered);
    resetHeldGem();
  }

  // Mouse input on adjacent gem to held one. Can be drag of click swap
  if (mouse_hold && Vec2i(gem_pos - _held_pos).dist() == 1) {
    _hovered_gem = nullptr;
    _held_gem->setState(Gem::State::Default);
    // Was not a drag, need to return Gem to Default
    if (mouse_press) {
      gem->setState(Gem::State::Default);
    }
    _swapped_pos = gem_pos;
    swapGems(_held_pos, _swapped_pos);
    _state                 = State::Swapping;
    _need_release_to_hover = true;
    SoundManager::instance()->playSFX(cSoundSwap);
    return;
  }

  // Mouse press but there was no swap
  if (mouse_press) {
    // Press again on held gem, mark next mouse release as unholding
    if (_held_gem == gem) {
      _unhold_on_release = true;
      return;
    }
    // Was not the held gem, release any previous hold and hold new one
    if (_held_gem != nullptr) {
      _held_gem->setState(Gem::State::Default);
    }
    _held_pos = gem_pos;
    _held_gem = gem;
    gem->setState(Gem::State::Pressed);
  }
}

void Board::handleInputSwapping() {
  if (_moving_gems) {
    return;
  }
  // Check for matches
  auto matches = searchMatches();
  if (matches.size() > 0) {
    _match_cycle = 1;
    breakGems(matches);
    resetSwapGems();
    _state = State::MovingGems;
  } else {
    // Reversing failed swap
    swapGems(_held_pos, _swapped_pos);
    _state = State::Reverting;
  }
}

void Board::handleInputReverting() {
  if (_moving_gems) {
    return;
  }
  resetSwapGems();
  _state = State::Default;
}

void Board::handleInputMovingGems() {
  if (_moving_gems) {
    return;
  }
  auto matches = searchMatches();
  // No match
  if (matches.size() == 0) {
    // There are possible matches if swapped
    if (searchHint(true) != Vec2i(-1, -1)) {
      _state = State::Default;
      return;
    }
    // No possible matches, reset board
    breakAllGems();
    fillBoard();
    SoundManager::instance()->playSFX(cSoundBreak);
    return;
  }
  // There is a match, break, and repeat.
  ++_match_cycle;
  breakGems(matches);
  resetSwapGems();
}
