//
// Created by Jiang Yinzuo on 2021/6/25.
//

#pragma once

#include "material.h"
#include "ray.h"
#include "hittable.h"

class dielectric : public material {
 public:
  explicit dielectric(double index_of_refraction) : ir(index_of_refraction) {}

   bool scatter(
	  const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered
  ) const override ;
 private:
  static double reflectance(double cosine, double ref_idx);
 public:
  double ir; // Index of Refraction
};

