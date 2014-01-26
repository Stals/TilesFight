#include "NeutralsSpawner.h"

#include "NeutralsHelper.h"
#include "ai/NoAI.h"
#include "utils/RandomGenerator.h"
#include "Game.h"

typedef void (NeutralSpawner::*spawnMethod)();


struct SpawnerType{
    SpawnerType(spawnMethod method, double weight):method(method), weight(weight){}
    
    spawnMethod method;
    double weight;
};


SpawnerType types[] = {
    SpawnerType(&NeutralSpawner::spawnSmallCapm, 5),
    SpawnerType(&NeutralSpawner::spawnBigSurroundedGenerator, 1)
};


NeutralSpawner::NeutralSpawner()
{
    neutral = Player::createNeutral();
	neutral->setAI(new NoAI(neutral));
}

NeutralSpawner& NeutralSpawner::current()
{
    static NeutralSpawner neutralSpawner;
    return neutralSpawner;
}


void NeutralSpawner::spawnRandomCamp()
{
    (this->*(types[0].method))();
}

void NeutralSpawner::spawnSmallCapm(){
    size_t x, y;
    getCoords(x, y);
    
    NeutralsHelper::addNeutrals( neutral, SmallGen, x, y);
}

void NeutralSpawner::spawnBigSurroundedGenerator()
{
    size_t center_x, center_y;
    getCoords(center_x, center_y);
    
	NeutralsHelper::addNeutrals(neutral, LargeGen, center_x, center_y);
	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = Game::current().getBoard()->sideHexAt((HexSide)side, center_x, center_y);
        if(hex)
            NeutralsHelper::addNeutrals(neutral, SmallGen, hex->getXCoord(), hex->getYCoord());
	}
}

void NeutralSpawner::getCoords(size_t &x, size_t &y)
{
    Board* board = Game::current().getBoard();
    x = RandomGenerator::getRandom(0, board->getHeight());
    y = RandomGenerator::getRandom(0, board->getWidth(y));
}


