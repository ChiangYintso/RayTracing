//
// Created by Jiang Yinzuo on 2021/6/22.
//

#pragma once
#include <iostream>
#include "vec3.h"

void write_color(std::ostream &out, color &pixel_color);
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel);