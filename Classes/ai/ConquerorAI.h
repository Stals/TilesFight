#pragma once
#include "AbstractAI.h"

class Hexagon;
class ConquerorAI : public AbstractAI
{
public:
	ConquerorAI(Player* player);

protected:
	virtual void doTurn(float dt);

private:

    // hexagon - вокруг чего начнется поиск
    Hexagon* getClosestUnoccupiedAddon(Hexagon* hexagon);
    
    // возвращает массив хесагонов вокруг переданных без дубликатов
    std::set<Hexagon*> getHexagonsAround(const std::set<Hexagon*> &hexagons);
};
