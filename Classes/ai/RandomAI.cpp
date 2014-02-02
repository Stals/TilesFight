#include "RandomAI.h"
#include "../Player.h"
#include "../Game.h"
#include "../utils/RandomGenerator.h"
#include "../Hexagon.h"

RandomAI::RandomAI(Player* player):AbstractAI(player)
{
}


void RandomAI::doTurn(float dt)
{
	if(player->getControlledHexagons().size() == 0) return;

	Hexagon* endHex = NULL;
	Hexagon* startHex = NULL;

	while(!endHex){
		startHex = getRandomControlledHexagon();
        if(!startHex) return; // no hexagons to move
        
		endHex = getRandomSideHexagon(startHex);
	}
    
    std::vector<Hexagon*> selectedHexagons;
	if(startHex->getTroopsCount() > 1){
		//startHex->setSelected(true);
		// todo wait a bit (schedule selector?)
        selectedHexagons.push_back(startHex);
		Game::current().getBoard()->moveTroops(selectedHexagons, endHex);
        //startHex->setSelected(false);
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
