
#include "Component.h"


class Missile_GreenComponent : public Component {
 public:
    Tag GetTag() override { return Tag::Missile_Green; }
    int GetType() override{ return Type::Green; }
};
