#ifndef TARGET_STONE
#define TARGET_STONE


#include "Component.h"


class Target_StoneComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Stone; }
};
#endif // !TARGET_STONE
