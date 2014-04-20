#include "NeutralsHelper.h"
#include "Game.h"

#define NEURALS_FACTOR 2


void NeutralsHelper::addNeutrals(Player* player, TroopsGenerator::Type type, size_t x, size_t y)
{
	addNeutrals(player, player, type, x, y);
}

void NeutralsHelper::addNeutrals(Player* player, Player* player2, TroopsGenerator::Type type, size_t x, size_t y)
{
    const int troopsCount = TroopsGenerator::getTroopsForType(type) * NEURALS_FACTOR;
    addNeutrals(player, player2, type, troopsCount, x, y);
}

void NeutralsHelper::addNeutrals(Player* player, Player* player2, TroopsGenerator::Type type, int troopsCount, size_t x, size_t y)
{
    Hexagon* hex = Game::current().getBoard()->at(x, y);
	if((!hex) || hex->getOwner()) return;
    
	Hexagon* sym_hex = getSymmetricHexagon(hex);
    
	hex->changeOwner(player);
	sym_hex->changeOwner(player2);
    
	hex->setAddon(new TroopsGenerator(hex, type));
	sym_hex->setAddon(new TroopsGenerator(sym_hex, type));
    
	hex->addTroops(troopsCount);
	sym_hex->addTroops(troopsCount);
}

void NeutralsHelper::addNeutrals(Player* player, AmoutIncreaser::Type type, size_t x, size_t y)
{
    addNeutrals(player, player, type, x, y);

}

void NeutralsHelper::addNeutrals(Player* player, Player* player2, AmoutIncreaser::Type type, size_t x, size_t y)
{
    Hexagon* hex = Game::current().getBoard()->at(x, y);
	if((!hex) || hex->getOwner()) return;
    
	Hexagon* sym_hex = getSymmetricHexagon(hex);
    
	hex->changeOwner(player);
	sym_hex->changeOwner(player2);
    
	hex->setAddon(new AmoutIncreaser(hex, type));
	sym_hex->setAddon(new AmoutIncreaser(sym_hex, type));
    
	hex->addTroops(50);
	sym_hex->addTroops(50);
}

/*
static void addNeutralWithAddon(Player* player, Player* player2, Addon* addon1, Addon* addon2, size_t x, size_t y)
{

}*/



void NeutralsHelper::getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y)
{
	sym_x = std::abs(Game::current().getBoard()->getWidth(y) - 1 - (int)x);
	sym_y = std::abs(Game::current().getBoard()->getHeight() - 1 - (int)y);
}

Hexagon* NeutralsHelper::getSymmetricHexagon(Hexagon* hex)
{
	size_t x, y;
	getSymmetricCoords(hex->getXCoord(), hex->getYCoord(), x, y);
	return Game::current().getBoard()->at(x, y);
}
