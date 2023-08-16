// Copyright (c) 2023 BD. All Rights Reserved.
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Allkit.h"
#include "Point.h"
#include "System.h"
#include <vector>

class RenderSystem : public System {
 public:
  RenderSystem(Engine &engine) : System(engine) { ak_ = &Allkit::Get(); }

  void Update();

  void DrawEntitys();

  bool InScreenWindow();

  void DrawScores();

 private:
  Allkit *ak_ = NULL;

  Point convert_to_Allegro_Coordinate_System(const Point);
};

#endif
