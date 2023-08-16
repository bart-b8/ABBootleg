#include "Component.h"


class Target_Component : public Component {
 public:
  Tag GetTag() override { return Tag::Target; }
  virtual ~Target_Component() {}
};
