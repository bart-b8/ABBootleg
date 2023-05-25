#ifndef SYSTEM_H
#define SYSTEM_H

class Engine;

class System {
    protected:
    
    Engine* engine_;

    public:

    virtual void Update() = 0;

    void SetEngine(Engine* engine);

};

#endif
