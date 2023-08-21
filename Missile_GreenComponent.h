#ifndef MISSILE_GREEN
#define MISSILE_GREEN

#include "Component.h"


class Missile_GreenComponent : public Component {
 public:
    Tag GetTag() override { return Tag::Missile_Green; }
    Type GetType() override{ return Type::Green; }
};
#endif // !MISSILE_GREEN
