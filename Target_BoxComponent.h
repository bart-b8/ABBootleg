
#include "Component.h"


class Target_BoxComponent : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Target_Box;
    }
};