#ifndef MISSILE_BLACKCOMP
#define MISSILE_BLACKCOMP

#include "Component.h"


class Missile_BlackComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Black; }

  Type GetType() override{ return Type::Black; }
};
#endif // !MISSILE_BLACKCOMP
