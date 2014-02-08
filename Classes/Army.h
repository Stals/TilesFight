#pragma once

#include "Hexagon.h"

class Army{
public:
    Army(Hexagon* hex, Point destination);

private:
    Hexagon* currentHex;
    Point destination;
    
    void move(float dt);
};
