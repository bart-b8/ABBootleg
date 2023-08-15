#include "Component.h"
#include "./Point.h"


class PositionComponent : public Component {
 public:
  Point pos;

  PositionComponent(Point position): pos(position) {}
  PositionComponent() {}

  Tag GetTag() override {
    return Tag::Position;
  }
};
