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
		endHex = getRandomSideHexagon(startHex);
	}

	if(startHex->getTroopsCount() > 1)
		Game::current().getBoard()->moveTroops(startHex, endHex);
}

Hexagon* RandomAI::getRandomControlledHexagon()
{
	std::set<Hexagon*>& hexagons = player->getControlledHexagons();
	size_t rnd = RandomGenerator::getRandom(0, hexagons.size());

	std::set<Hexagon*>::iterator it = hexagons.begin();
	std::advance(it, rnd);

	return *it;
}

Hexagon* RandomAI::getRandomSideHexagon(Hexagon* hex)
{
	HexSide randomSide = (HexSide)RandomGenerator::getRandom(0, HexSidesCount);
	return Game::current().getBoard()->sideHexAt(randomSide, hex->getXCoord(), hex->getYCoord());
}
