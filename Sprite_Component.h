#ifndef SPRITECOMP
#define SPRITECOMP

#include "Component.h"
#include "./Sprite.h"
#include "./Config.h"


class Sprite_Component : public Component {
 public:
  enum Sprite sprite;

  float src_width = Config::Get().Map()["missiles.src_width"];
  float src_height = Config::Get().Map()["missiles.src_height"];
  float dst_width = Config::Get().Map()["missiles.dst_width"];
  float dst_height = Config::Get().Map()["missiles.dst_height"];

  Tag GetTag() override {
      return Tag::Sprite;
  }

  virtual ~Sprite_Component() {}
};

#endif  // SPRITECOMP
