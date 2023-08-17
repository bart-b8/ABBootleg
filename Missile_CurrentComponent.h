#ifndef CURRENTCOMP
#define CURRENTCOMP

#include "Component.h"
#include "./Point.h"


class Missile_CurrentComponent : public Component {
 public:
  Point vel;

    Tag GetTag() override {
        return Tag::Missile_Current;
    }
};
#endif // !CURRENTCOMP
