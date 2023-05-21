#ifndef LAUNCHERSYSTEM_H
#define LAUNCHERSYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"

class LauncherSystem : public System {
  public:
    void Update();

    void CreateQueue(std::vector<int> vec_queue);

    void AddToQueue(std::vector<int> vec_queue, int AddMissile);

    double WeightedAverage();

    void MouseLocation();

    bool MouseOnMissile();

    void MouseRecord();

  private:
    std::vector<int> vec_queue;
    std::vector<double> vec_coordinates;
};

#endif
