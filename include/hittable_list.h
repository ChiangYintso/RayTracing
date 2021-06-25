//
// Created by Jiang Yinzuo on 2021/6/24.
//

#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <hittable.h>

using std::shared_ptr;

class hittable_list : public Hittable {
 public:
  hittable_list() = default;
  hittable_list(shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(shared_ptr<Hittable> object) { objects.push_back(object); }

  bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

 public:
  std::vector<shared_ptr<Hittable>> objects;
};
