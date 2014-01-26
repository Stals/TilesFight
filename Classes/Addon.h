#pragma once

#include "Hexagon.h"

class Addon : public CCNode{
public:
    Addon(Hexagon* hex);
    
protected:
    Hexagon* hex;
};
