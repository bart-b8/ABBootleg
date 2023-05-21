#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include "Allkit.h"
#include "Point.h"
#include "System.h"

class RenderSystem : public System {
  public:
    void DrawEntitys();

    bool InScreenWindow();

    void DrawScores();

  private:

};




#endif
