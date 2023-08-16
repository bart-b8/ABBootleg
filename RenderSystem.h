// Copyright (c) 2023 BD. All Rights Reserved.
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Allkit.h"
#include "Point.h"
#include "System.h"
#include <vector>

class RenderSystem : public System {
 public:
  RenderSystem(Engine &engine) : System(engine) {}

  void Update();

  void DrawEntitys();

  bool InScreenWindow();

  void DrawScores();
};

#endif
