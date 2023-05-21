
#include "Component.h"


class Missile_YellowComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Missile_Yellow;
    }

    virtual int GetType() override{
        return Type::Yellow;
    }
};