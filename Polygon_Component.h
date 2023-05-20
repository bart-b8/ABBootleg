
#include "Component.h"

class Polygon_Component : public Component {
public:
    double width;
    double height;
    double x;
    double y;

    Tag GetTag() override {
        return Tag::Polygon;
    }
};