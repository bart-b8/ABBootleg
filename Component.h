#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
  public:
    enum Tag {
        // TODO
    };

    virtual Tag GetTag() = 0;

    // Geeft de kans terug dat een bepaalde missile component voorkomt
    virtual int GetWeight(int level) { return -1; };

    // Geeft het type van een missile component terug
    virtual int GetType() { return -1; };
};

#endif
