
#include "Component.h"


class Target_BoxComponent : public Component {
 public:
  Tag GetTag() override { return Tag::Target_Box; }
};
