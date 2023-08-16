#ifndef SYSTEM_H
#define SYSTEM_H

#include "Allkit.h"
#include <vector>

class Engine;

class System {
 protected:
  Engine &engine_;

  Allkit *ak_ = NULL;

  bool CheckCollision(std::vector<Point> &coordinates_poly_one, std::vector<Point> &coordinates_poly_two);

 public:
  System(Engine &engine): engine_(engine) { ak_ = &Allkit::Get(); }

  virtual void Update() = 0;

  Point convert_to_Allegro_Coordinate_System(const Point classic);

  Point convert_to_Classic_Coordinate_System(const Point allegro);

  virtual ~System() {}

 private:
  std::vector<Point> GetEdges(std::vector<Point> &coordinates);

  void ProjectOnAxis(std::vector<Point> &coordinates, Point &axis, double &min, double &max);

  double DistanceBetweenPolys(double min_a, double max_a, double min_b, double max_b);
};

#endif
