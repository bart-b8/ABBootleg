
#include "Component.h"


class Target_StoneComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Target_Stone;
    }
};