#ifndef POINT_H
#define POINT_H

#include <math.h>

class Point {
  public:
    double x_, y_;

    Point(){};
    Point(double x, double y) : x_(x), y_(y){};

    double operator*(const Point &o) {
        // TODO
        return 0;
    }

    Point operator-(const Point &o) {
        return Point(x_-o.x_,y_-o.y_);
    }

    double operator>>(const Point &o) {
        // TODO
        return 0;
    }

    double Length() {
        // TODO
        return sqrt(pow(x_,2) + pow(y_,2));
    }

    void Normalize() {
        // TODO
    }
};

#endif
