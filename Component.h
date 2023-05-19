#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
  public:
    enum Tag {
      Target_box,
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
    };

    virtual Tag GetTag() = 0;

    // Geeft de kans terug dat een bepaalde missile component voorkomt
    virtual int GetWeight(int level) { return -1; };

    // Geeft het type van een missile component terug
    virtual int GetType() { return -1; };
};

#endif
