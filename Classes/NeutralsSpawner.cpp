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
    SpawnerType(&NeutralSpawner::spawnSmall, 5),
    SpawnerType(&NeutralSpawner::spawnBigSurroundedGenerator, 1),
    SpawnerType(&NeutralSpawner::spawnSmallCluster, 3),
    SpawnerType(&NeutralSpawner::spawnMedium, 4),
    SpawnerType(&NeutralSpawner::spawnMediumCamp, 1)
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
    (this->*(types[4].method))();
}


void NeutralSpawner::getCoords(size_t &x, size_t &y)
{
    Board* board = Game::current().getBoard();
    x = RandomGenerator::getRandom(0, board->getHeight());
    y = RandomGenerator::getRandom(0, board->getWidth(y));
}

void NeutralSpawner::spawnSmall(){
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

void NeutralSpawner::spawnSmallCluster()
{
    size_t x, y;
    getCoords(x, y);
    
    NeutralsHelper::addNeutrals( neutral, SmallGen, x, y);
    NeutralsHelper::addNeutrals( neutral, SmallGen, x, y-1);
    NeutralsHelper::addNeutrals( neutral, SmallGen, x-1, y);
    NeutralsHelper::addNeutrals( neutral, SmallGen, x-1, y-1);

}

void NeutralSpawner::spawnMedium()
{
    size_t x, y;
    getCoords(x, y);
    NeutralsHelper::addNeutrals( neutral, MediumGen, x, y);
}

void NeutralSpawner::spawnMediumCamp(){
    const size_t smallOnSides = RandomGenerator::getRandom(1, 4);
    
    size_t center_x, center_y;
    getCoords(center_x, center_y);

    NeutralsHelper::addNeutrals( neutral, MediumGen, center_x, center_y);

    for(size_t i = 0; i < smallOnSides; ++i){
        HexSide rndSide = (HexSide)RandomGenerator::getRandom(0, HexSidesCount);
        Hexagon* hex = Game::current().getBoard()->sideHexAt(rndSide, center_x, center_y);
        if(hex)
            NeutralsHelper::addNeutrals(neutral, SmallGen, hex->getXCoord(), hex->getYCoord());
        
    }
    
}




