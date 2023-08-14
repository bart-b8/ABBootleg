#ifndef CONTEXT_H
#define CONTEXT_H

#include <filesystem>

// TODO(BD): Moet dit niet een singleton klasse zijn? 
// Ik vraag me dit of omdat de Context ook gedeeld wordt tijdens het spel
// en er geen twee tegelijkertijd kunnen bestaan.
class Context {
    public: 
        std::filesystem::path pth_level;
};

#endif
