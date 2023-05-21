#ifndef MISSILESYSTEM_H
#define MISSILESYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"

class MissileSystem : public System {
  public:
    void Update();

    void LaunchMissile();

    void Elastic();

    void MissileAbility();

    void MissileRecord();

    private:

};

#endif
