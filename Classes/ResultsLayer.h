#pragma once

#include "PauseLayer.h"
#include "Game.h"

class ResultsLayer : public PauseLayer{
public:
    ResultsLayer(Player* winner);
    
private:
    void setupLabel(Player* winner);
    
    std::string getText(Player* winner);
};