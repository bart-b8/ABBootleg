#ifndef TARGET_CIRCLE
#define TARGET_CIRCLE

#include "Component.h"


class Target_CircleComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Circle; }
};
#endif // !TARGET_CIRCLE
