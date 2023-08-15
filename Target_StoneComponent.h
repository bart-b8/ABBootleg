
#include "Component.h"


class Target_StoneComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Stone; }
};
