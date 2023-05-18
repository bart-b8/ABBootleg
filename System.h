#ifndef SYSTEM_H
#define SYSTEM_H

class System {
    protected:
    
    Engine* engine;

    public:

    virtual void Update() = 0;

    void SetEngine(Engine* engine);

};

#endif
