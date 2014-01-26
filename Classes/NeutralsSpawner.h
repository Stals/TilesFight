#pragma once
#include "Player.h"


class NeutralSpawner{
public:
    static NeutralSpawner& current();
    
    void spawnRandomCamp();
    
    
    // different spawners
    void spawnSmallCapm();
    void spawnBigSurroundedGenerator();
    
private:
    NeutralSpawner();
    
    void getCoords(size_t &x, size_t &y);
    
    Player* neutral;
};



