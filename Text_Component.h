#ifndef TEXTCOMP
#define TEXTCOMP

#include "./Component.h"
#include "./Color.h"
#include "./Allkit.h"
#include <string>


class Text_Component : public Component {
 public:
  Tag GetTag() override {
    return Tag::Text;
  }

  std::string text;
  Color color;
  enum Allkit::Align align = Allkit::ALIGN_LEFT;
  bool huge_font = false;
};

#endif // TEXTCOMP
