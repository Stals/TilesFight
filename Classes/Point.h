#pragma once

#include <stddef.h> // for size_t

struct Point{
    Point(size_t x, size_t y):x(x), y(y){}
    size_t x;
    size_t y;
};
