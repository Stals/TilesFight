#include "RandomAI.h"
#include "../Player.h"
#include "../Game.h"
#include "../utils/RandomGenerator.h"
#include "../Hexagon.h"

#define MAX_ATTEMPTS 10

RandomAI::RandomAI(Player* player):AbstractAI(player)
{
}


void RandomAI::doTurn(float dt)
{
	if(player->getControlledHexagons().size() == 0) return;

	Hexagon* endHex = NULL;
	Hexagon* startHex = NULL;

    size_t attempt = 0;
	while(!endHex || attempt >= MAX_ATTEMPTS){
        ++attempt;
        
		startHex = getRandomControlledHexagon();
        if(!startHex) return; // no hexagons to move
        
		endHex = getRandomSideHexagon(startHex);
	}
    
    std::vector<Hexagon*> selectedHexagons;
	if(startHex->getTroopsCount() > 1){
        TroopsMover::moveTroops(startHex->createArmy(endHex), endHex);
	}
}

Hexagon* RandomAI::getRandomControlledHexagon()
{
    std::vector<Hexagon*> hexagons = player->getHexagonsWithTroops();
    
    if(!hexagons.empty()){
        size_t rnd = RandomGenerator::getRandom(0, hexagons.size());
        return hexagons[rnd];
    }else{
        return NULL;
    }
}

Hexagon* RandomAI::getRandomSideHexagon(Hexagon* hex)
{
	HexSide randomSide = (HexSide)RandomGenerator::getRandom(0, HexSidesCount);
	return Game::current().getBoard()->sideHexAt(randomSide, hex->getXCoord(), hex->getYCoord());
}
