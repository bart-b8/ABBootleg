#ifndef SYSTEM_H
#define SYSTEM_H

#include "Allkit.h"
class Engine;

class System {
 protected:
  Engine &engine_;

  Allkit *ak_ = NULL;

 public:
  System(Engine &engine): engine_(engine) { ak_ = &Allkit::Get(); }

  virtual void Update() = 0;

  Point convert_to_Allegro_Coordinate_System(const Point classic);

  Point convert_to_Classic_Coordinate_System(const Point allegro);

  virtual ~System() {}
};

#endif
