//
// Created by Jiang Yinzuo on 2021/6/25.
//

#include <color.h>

int main() {
  const int image_width = 600;
  const int image_height = 400;
  const int samples_per_pixel = 100;

  JPGWriter jpg_writer("hello.jpg", image_width, image_height);

  for (int j = image_height-1; j >= 0; --j) {
	std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
	for (int i = 0; i < image_width; ++i) {
	  color pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);
	  jpg_writer.WriteColor(pixel_color, samples_per_pixel);
	}
  }
  std::cerr << "\nDone.\n";

  return 0;
}