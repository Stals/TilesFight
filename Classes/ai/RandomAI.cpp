#include "RandomAI.h"
#include "../Player.h"
#include "../Game.h"

RandomAI::RandomAI(Player* player):AbstractAI(player)
{
}


void RandomAI::doTurn(float dt)
{
	std::set<Hexagon*>& hexagons = player->getControlledHexagons();

	for(std::set<Hexagon*>::iterator it = hexagons.begin(); it != hexagons.end(); ++it){
		Hexagon* hex = *it;
		Hexagon* endHex = Game::current().getBoard()->sideHexAt(HexTopLeft, hex->getXCoord(), hex->getYCoord());

		if(endHex){
			Game::current().getBoard()->moveTroops(hex, endHex);
			break;
		}
	}
}