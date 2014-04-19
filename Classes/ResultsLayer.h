#pragma once

#include "PauseLayer.h"
#include "Game.h"

class ResultsLayer : public PauseLayer{
public:
    ResultsLayer(Player* winner, Player* looser);
    
private:
    void setupLabel(Player* winner);
    
    std::string getText(Player* winner);
    
    void updateAchievements(Player* winner, Player* looser);
    void checkOneTimeAchievements(Player* winner);
    
    // control all sectors
    bool checkTotalControl(Player* winner);
    // control all neutrals
    bool checkNeutralsControl(Player* winner);
    
    void increaseAiCounter(Player* looser);
};