
#include "Component.h"

class Polygon_Component : public Component {
 public:
  double width;
  double height;

  Tag GetTag() override {
      return Tag::Polygon;
  }
};
