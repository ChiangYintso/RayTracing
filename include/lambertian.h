//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include "ray.h"
#include "hittable.h"
#include "material.h"

class lambertian : public material {
 public:
  explicit lambertian(const color &a) : albedo(a) {}

  bool scatter(
	  const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered
  ) const override;

 public:
  color albedo;
};



