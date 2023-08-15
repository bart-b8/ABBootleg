#include "Component.h"

class Missile_YellowComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Missile_Yellow; }
  int GetType() override{ return Type::Yellow; }
};
