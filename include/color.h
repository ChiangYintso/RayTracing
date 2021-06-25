//
// Created by Jiang Yinzuo on 2021/6/22.
//

#pragma once
#include <iostream>
#include "vec3.h"

const color kBlackColor = color{0, 0, 0};

void write_color(std::ostream &out, color &pixel_color);
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel);

class JPGWriter {
 public:
  JPGWriter(const char *file_name, int w, int h);

  JPGWriter(const JPGWriter &w) = delete;
  JPGWriter &operator=(const JPGWriter &w) = delete;

  ~JPGWriter();

  void WriteColor(color pixel_color, int samples_per_pixel);

 private:
  const char *file_name_;
  int w_;
  int h_;
  unsigned char *data_;
  int pixel_idx_ = 0;
};