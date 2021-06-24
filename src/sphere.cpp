//
// Created by Jiang Yinzuo on 2021/6/24.
//

#include "sphere.h"

bool Sphere::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) return false;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
	root = (-half_b + sqrtd) / a;
	if (root < t_min || t_max < root)
	  return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - center) / radius;
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  return true;
}
