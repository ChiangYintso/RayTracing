//
// Created by Jiang Yinzuo on 2021/6/25.
//

#include "camera.h"
#include "constants.h"
#include "utils.h"
#include "lambertian.h"
#include "metal.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <memory>
#include <iostream>

using std::make_shared;

color ray_color(const Ray &r, const Hittable &world, int depth) {
  hit_record rec;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
	return kBlackColor;

  if (world.hit(r, 0.001, infinity, rec)) {
	Ray scattered;
	color attenuation;
	if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
	  return attenuation * ray_color(scattered, world, depth - 1);
	return color(0, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

  // Image

  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // World

  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  auto material_left = make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3);
  auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

  world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

  // Camera

  point3 lookfrom(3,3,2);
  point3 lookat(0,0,-1);
  vec3 vup(0,1,0);
  auto dist_to_focus = (lookfrom-lookat).length();
  auto aperture = 2.0;

  Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  // Render

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
	std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
	for (int i = 0; i < image_width; ++i) {
	  color pixel_color(0, 0, 0);
	  for (int s = 0; s < samples_per_pixel; ++s) {
		auto u = (i + random_double()) / (image_width - 1);
		auto v = (j + random_double()) / (image_height - 1);
		Ray r = cam.get_ray(u, v);
		pixel_color += ray_color(r, world, max_depth);
	  }
	  write_color(std::cout, pixel_color, samples_per_pixel);
	}
  }

  std::cerr << "\nDone.\n";
}