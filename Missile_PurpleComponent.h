
#include "Component.h"


class Missile_PurpleComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Missile_Purple;
    }

    virtual int GetType() override{
        return Type::Purple;
    }
};