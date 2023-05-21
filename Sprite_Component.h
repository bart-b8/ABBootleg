
#include "Component.h"


class Sprite_Component : public Component {
public:

    int sprite;

    Tag GetTag() override {
        return Tag::Sprite;
    }
};