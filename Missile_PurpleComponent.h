#ifndef MISSILE_PURP
#define MISSILE_PURP

#include "Component.h"


class Missile_PurpleComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Purple; }
  Type GetType() override{ return Type::Purple; }
};
#endif // !MISSILE_PURP
