
#include "Component.h"


class Missile_PurpleComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Purple; }
  int GetType() override{ return Type::Purple; }
};
