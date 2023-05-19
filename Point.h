#ifndef POINT_H
#define POINT_H
#include <cmath>

#include <math.h>

class Point {
  public:
    double x_, y_;

    Point(){};
    Point(double x, double y) : x_(x), y_(y){};


    Point operator-(const Point &o) {
        return Point(x_-o.x_,y_-o.y_);
    }

    double operator>>(const Point &o) {
        return x_*o.x_ + y_*o.y_ ;
    }

    double Length() {
        return sqrt(pow(x_,2) + pow(y_,2));
    }

    double operator*(const Point &o) {
        return (*this-o).Length();
    }

    void Normalize() {
        double l = Length();
        if (1!=0.0) {
            x_ = x_/l;
            y_ = y_/l; 

        }
    }
};

#endif
