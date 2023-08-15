
#include "Component.h"


class Missile_BlackComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Black; }

  int GetType() override{ return Type::Black; }
};
