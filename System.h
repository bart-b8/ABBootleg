#ifndef SYSTEM_H
#define SYSTEM_H

class Engine;

class System {
 protected:
  Engine &engine_;

 public:
  System(Engine &engine): engine_(engine) {}

  virtual void Update() = 0;
};

#endif
