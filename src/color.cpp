//
// Created by Jiang Yinzuo on 2021/6/22.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <color.h>

#include "utils.h"
#include "vec3.h"

void write_color(std::ostream &out, color &pixel_color) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
	  << static_cast<int>(255.999 * pixel_color.y()) << ' '
	  << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples and gamma-correct for gamma=2.0.
  auto scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
	  << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
	  << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

JPGWriter::JPGWriter(const char *file_name, int w, int h) : file_name_(file_name), w_(w), h_(h) {
  data_ = (unsigned char *) malloc(w * h * 3);
}

JPGWriter::~JPGWriter() {
  stbi_write_jpg(file_name_, w_, h_, 3, data_, 0);
  free(data_);
}

void JPGWriter::WriteColor(color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples and gamma-correct for gamma=2.0.
  auto scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);
  data_[pixel_idx_ * 3] = static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999));
  data_[pixel_idx_ * 3 + 1] = static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999));
  data_[pixel_idx_ * 3 + 2] = static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999));
  ++pixel_idx_;
}
