
#include "Component.h"
#include "./Sprite.h"


class Sprite_Component : public Component {
 public:
    enum Sprite sprite;

    Tag GetTag() override {
        return Tag::Sprite;
    }
};
