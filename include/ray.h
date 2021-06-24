//
// Created by Jiang Yinzuo on 2021/6/22.
//

#pragma once

#include "vec3.h"

class Ray {
 public:
  Ray() = default;
  Ray(const point3 &origin, const vec3 &direction)
	  : orig(origin), dir(direction) {}

  [[nodiscard]] point3 origin() const { return orig; }
  [[nodiscard]] vec3 direction() const { return dir; }

  [[nodiscard]] point3 at(double t) const {
	return orig + t * dir;
  }

 public:
  point3 orig;
  vec3 dir;
};
