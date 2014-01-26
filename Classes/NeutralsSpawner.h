#pragma once
#include "Player.h"

// TODO добавить интересный тип у которого маленькая вероятность -
// но например он всегда в заданых местах
// Например: по середине стена

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
    size_t getRandomTypeID();
    
    Player* neutral;
};



