#pragma once

#include "src/begemmed/game_objects/Gem.h"
#include "src/engine/game_objects/GameObject.h"

#include <random>

class Board : public GameObject {
  public:
    Board(Vec2f pos, int width, int height);

    virtual void update(int delta_time) override;
    virtual void render() const override;

    Vec2i searchHint(bool instant = false);
    void breakAllGems(bool instant = false, bool game_is_over = false);

    virtual ~Board();

  private:
    enum class State {
      Default,
      Swapping,
      Reverting,
      MovingGems,
    };

    const int _width;
    const int _height;
    std::default_random_engine _generator;
    std::vector<std::vector<Gem*>> _board_gems;

    bool _game_is_over {false};
    bool _moving_gems {false};
    bool _unhold_on_release {false};
    bool _need_release_to_hover {false};

    std::vector<Gem*> _being_destroyed_gems;
    Gem* _hovered_gem {nullptr};
    Gem* _held_gem {nullptr};
    Gem* _hinted_gem {nullptr};
    Vec2i _held_pos {-1, -1};
    Vec2i _swapped_pos {-1, -1};
    State _state {State::Default};
    int _match_cycle {1};

    std::vector<Gem*> addGems(int x, int amount);
    void fillBoard(bool instant = false);
    void destroyGem(int x, int y, bool instant = false);
    int calculateScore(int amount) const;
    void breakGems(std::vector<std::vector<Vec2i>> gems_pos, bool instant = false);
    std::vector<std::vector<Vec2i>> searchMatches();

    Vec2f matrixToRealPos(Vec2i mat_pos) const;
    void resetHeldGem();
    void resetSwapGems();
    void swapGems(Vec2i pos1, Vec2i pos2);

    void handleInput();
    void handleInputDefault();
    void handleInputSwapping();
    void handleInputReverting();
    void handleInputMovingGems();
};
