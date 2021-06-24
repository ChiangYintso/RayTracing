//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include <vec3.h>
#include <hittable.h>

class Sphere : public Hittable {
 public:
  point3 center;
  double radius;

  Sphere() = default;
  Sphere(point3 cen, double r) : center(cen), radius(r) {}
  bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};



