#pragma once

#include <stddef.h> // for size_t

struct Point{
    Point(int x, int y):x(x), y(y){}
    int x;
    int y;
    
    
    // для быстрого расчета относительного расстояния
    // TODO использовать для A*? - cравнить разницу в скорости
    // хотя там лучше запилить не пересоздавание каждый раз кучи объектов
    int distanceSquared(const Point& other) const
    {
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
    }

    
    bool operator==(const Point& other)
    {
        return (x == other.x) && (y == other.y);
    }
};
