#pragma once
#include "AbstractAI.h"

class Hexagon;
class ExpansionAI : public AbstractAI
{
public:
	ExpansionAI(Player* player);

protected:
	virtual void doTurn(float dt);
    

private:
    Hexagon* center;
    Hexagon* currentTarget;
    
    void setupCenter();
    Hexagon* getClosestUnoccupiedHexagon();
    
    void sendArmies(Hexagon* target);
    
    // возвращает массив хесагонов вокруг переданных без дубликатов
    std::set<Hexagon*> getHexagonsAround(const std::set<Hexagon*> &hexagons);
};
