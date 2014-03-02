#pragma once

#include "PauseLayer.h"
#include "Game.h"


class ResultsLayer : public PauseLayer{
public:
    ResultsLayer(Game::Type gameType, int playerID);
    
private:
    void setupLabel(Game::Type gameType, int playerID);
    
    std::string getText(Game::Type gameType, int playerID);
};