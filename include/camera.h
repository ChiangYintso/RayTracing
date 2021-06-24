//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include "vec3.h"
#include "ray.h"

class camera {
 public:
  camera();

  [[nodiscard]] Ray get_ray(double u, double v) const {
	return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
  }

 private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};

