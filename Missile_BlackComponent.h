
#include "Component.h"


class Missile_BlackComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Missile_Black;
    }

    virtual int GetType() override{
        return Type::Black;
    }
};