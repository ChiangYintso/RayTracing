//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include <vec3.h>
#include <hittable.h>

#include <utility>

class Sphere : public Hittable {
 public:
  point3 center;
  double radius{};
  shared_ptr<material> mat_ptr;

  Sphere() = default;
  Sphere(point3 cen, double r) : center(cen), radius(r) {}
  Sphere(point3 cen, double r, shared_ptr<material> m)
  : center(cen), radius(r), mat_ptr(std::move(m)) {};
  bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};



