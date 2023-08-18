#include "Component.h"
#include "./Sprite.h"


class Target_Component : public Component {
 public:
  int i;
  int j;
  int ii;
  enum Sprite normal;
  enum Sprite hit;
  Tag GetTag() override { return Tag::Target; }
  virtual ~Target_Component() {}
};
