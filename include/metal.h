//
// Created by Jiang Yinzuo on 2021/6/25.
//

#pragma once

#include "ray.h"
#include "material.h"
#include "vec3.h"
#include "hittable.h"

class Metal : public material {
 public:
  explicit Metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  virtual bool scatter(
	  const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered
  ) const override {
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
  }

 public:
  color albedo;
  double fuzz;
};
