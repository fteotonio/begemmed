#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2(T new_x, T new_y) : x(new_x), y(new_y) {}

    Vec2() : Vec2(0, 0) {}

    float dist() const {
      return sqrt(x * x + y * y);
    }

    Vec2<T> operator+(const Vec2<T>& rhs) const {
      return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2<T> operator-(const Vec2<T>& rhs) const {
      return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2<T>& operator+=(const Vec2<T>& rhs) {
      x += rhs.x;
      y += rhs.y;
      return *this;
    }

    Vec2<T>& operator-=(const Vec2<T>& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      return *this;
    }

    Vec2<T> operator/(const T& rhs) const {
      return Vec2(x / rhs, y / rhs);
    }

    Vec2<T> operator-() const {
      return Vec2(-x, -y);
    }

    bool operator==(const Vec2<T>& rhs) const {
      return (x == rhs.x) && (y == rhs.y);
    }

    bool operator!=(const Vec2<T>& rhs) const {
      return (x != rhs.x) || (y != rhs.y);
    }

    bool operator<(const Vec2<T>& rhs) const {
      return dist() < rhs.dist();
    }

    // Allow converting Vec2i to Positions
    operator Vec2<float>() const {
      return Vec2<float>(static_cast<float>(x), static_cast<float>(y));
    }
};

template<typename T>
Vec2<T> operator*(const Vec2<T>& v, const T& t) {
  return Vec2<T>(v.x * t, v.y * t);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
  os << "(x: " << v.x << ", y: " << v.y << ")";
  return os;
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
