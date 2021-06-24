//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include <cmath>

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}