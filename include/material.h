//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include "ray.h"
#include "color.h"

struct hit_record;

class material {
 public:
  virtual bool scatter(
	  const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered
  ) const = 0;
};
