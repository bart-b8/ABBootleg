
#include "Component.h"


class Missile_GreenComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Missile_Green;
    }
};