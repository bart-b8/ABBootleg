#include "Component.h"


class Target_Component : public Component {
 public:
  int i;
  int j;
  int ii;
  Tag GetTag() override { return Tag::Target; }
  virtual ~Target_Component() {}
};
