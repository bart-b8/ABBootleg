#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
 public:
  enum Tag {
    Target_Box,
    Target_Circle,
    Target_Stone,
    Missile_Current,
    Missile_Yellow,
    Missile_Purple,
    Missile_Green,
    Missile_Black,
    Target,
    Polygon,
    Sprite,
    Position,
    Text,
  };
  enum Type {
    Yellow,
    Purple,
    Green,
    Black,
  };

  virtual Tag GetTag() = 0;

  // Geeft de kans terug dat een bepaalde missile component voorkomt
  virtual int GetWeight(int level) { return -1; }

  // Geeft het type van een missile component terug
  virtual Type GetType() { return Yellow; }

  virtual ~Component() {}
};

// TODO(BD): ifndef in all .h files of components.
//
#endif
