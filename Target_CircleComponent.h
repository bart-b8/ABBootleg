
#include "Component.h"


class Target_CircleComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Circle; }
};
