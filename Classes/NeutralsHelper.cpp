#include "NeutralsHelper.h"
#include "Game.h"

#define NEURALS_FACTOR 2

// TODO должен не спавнить на игроках или мимо краты!
void NeutralsHelper::addNeutrals(Player* player, GeneratorType type, size_t x, size_t y)
{
	Hexagon* hex = Game::current().getBoard()->at(x, y);
	if((!hex) || hex->getOwner()) return;

	Hexagon* sym_hex = getSymmetricHexagon(hex);

	hex->changeOwner(player);
	sym_hex->changeOwner(player);

	hex->setGenerator(new TroopsGenerator(hex, type));
	sym_hex->setGenerator(new TroopsGenerator(sym_hex, type));

	hex->addTroops(TroopsGenerator::getTroopsForType(type) * NEURALS_FACTOR);
	sym_hex->addTroops(TroopsGenerator::getTroopsForType(type) * NEURALS_FACTOR);
}


void NeutralsHelper::getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y)
{
	sym_x = std::abs(Game::current().getBoard()->getWidth() - 1 - (int)x);
	sym_y = std::abs(Game::current().getBoard()->getHeight() - 1 - (int)y);
}

Hexagon* NeutralsHelper::getSymmetricHexagon(Hexagon* hex)
{
	size_t x, y;
	getSymmetricCoords(hex->getXCoord(), hex->getYCoord(), x, y);
	return Game::current().getBoard()->at(x, y);
}
