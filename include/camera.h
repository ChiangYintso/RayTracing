//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include "vec3.h"
#include "ray.h"

class camera {
 public:
  camera(
	  point3 lookfrom,
	  point3 lookat,
	  vec3   vup,
	  double vfov, // vertical field-of-view in degrees
	  double aspect_ratio,
	  double aperture,
	  double focus_dist
  );

  [[nodiscard]] Ray get_ray(double s, double t) const;

 private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  double lens_radius;
};

