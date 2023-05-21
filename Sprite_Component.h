
#include "Component.h"


class Sprite_Component : public Component {
public:



    Tag GetTag() override {
        return Tag::Sprite;
    }
};