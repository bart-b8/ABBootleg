
#include "Component.h"


class Missile_CurrentComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Missile_Current;
    }
};