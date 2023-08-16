#include <vector>

#include "./Point.h"
#include "Component.h"

class Polygon_Component : public Component {
 public:
  std::vector<Point> body_;

  Polygon_Component(std::vector<Point> body): body_(body) {}
  Polygon_Component() {}

  Tag GetTag() override {
      return Tag::Polygon;
  }
};
