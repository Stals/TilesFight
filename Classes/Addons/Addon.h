#pragma once

#include "Hexagon.h"

class Addon : public CCNode{
public:
    Addon(Hexagon* hex);
    
    virtual CCNode* getIcon() = 0;
    
protected:
    Hexagon* hex;
};
