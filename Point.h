#ifndef POINT_H
#define POINT_H
#include <cmath>

class Point {
  public:
    double x_, y_;

    Point(){};
    Point(double x, double y) : x_(x), y_(y){};

    double operator*(const Point &o) {
        double x_2 = o.x_ - x_;
        double y_2 = o.y_ - y_;
        return sqrt(x_2 * x_2 + y_2 * y_2);
    }
        

    Point operator-(const Point &o) {
        double x_2 = o.x_ - x_;
        double y_2 = o.y_ - y_;
        return Point(x_2,y_2);
    }

    double operator>>(const Point &o) {
        return (x_ * o.x_ + y_ * o.y_) / sqrt(o.x_*o.x_ +o.y_*o.y_ );        
    }

    double Length() {
        return sqrt(x_*x_ +y_*y_ );
    }

    void Normalize() {
        double l =Length();
        if (l != 0.0){
            x_= x_/l;
            y_=y_/l;
        }
    }
};

#endif
