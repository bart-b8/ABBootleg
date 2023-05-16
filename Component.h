#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
  public:
    enum Tag {
        Target_BoxComponent,
        Target_CircleComponent,
        Target_DiamondComponent,
        Current_MissileComponent,
        Missile_YellowComponent,
        Missile_PurpleComponent,
        Missile_GreenComponent,
        Missile_BlackComponent,
        //PolygonComponent,
        //SpriteComponent,
        //TargetComponent,
    };

    virtual Tag GetTag() = 0;

    // Geeft de kans terug dat een bepaalde missile component voorkomt
    virtual int GetWeight(int level) { return -1; };

    // Geeft het type van een missile component terug
    virtual int GetType() { return -1; };
};

#endif
