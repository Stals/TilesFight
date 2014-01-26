#pragma once
#include "Player.h"


class NeutralSpawner{
public:
    static NeutralSpawner& current();
    
    void spawnRandomCamp();
    
    
    // different spawners
    void spawnSmall();
    void spawnBigSurroundedGenerator();
    void spawnSmallCluster();
    void spawnMedium();
    void spawnMediumCamp();
    
    
private:
    NeutralSpawner();
    
    void getCoords(size_t &x, size_t &y);
    
    Player* neutral;
};



