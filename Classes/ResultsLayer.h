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
    void increaseAiCounter(Player* looser);
};