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
    
    Player* neutral;
};



