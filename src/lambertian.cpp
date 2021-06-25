//
// Created by Jiang Yinzuo on 2021/6/24.
//

#include "lambertian.h"

bool lambertian::scatter(const Ray &r_in, const hit_record &rec, color &attenuation, Ray &scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector();

  // Catch degenerate scatter direction
  if (scatter_direction.near_zero())
	scatter_direction = rec.normal;

  scattered = Ray(rec.p, scatter_direction);
  attenuation = albedo;
  return true;
}
