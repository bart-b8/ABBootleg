#ifndef MISSILE_YELLOW
#define MISSILE_YELLOW
#include "Component.h"

class Missile_YellowComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Yellow; }
  Type GetType() override{ return Type::Yellow; }
};
#endif // !MISSILE_YELLOW
