#ifndef TARGET_BOX
#define TARGET_BOX


#include "Component.h"


class Target_BoxComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Box; }
};
#endif // !TARGET_BOX
