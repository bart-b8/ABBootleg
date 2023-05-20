
#include "Component.h"


class Target_Component : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Target;
    }
};