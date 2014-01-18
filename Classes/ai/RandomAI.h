#pragma once
#include "AbstractAI.h"

class Hexagon;
class RandomAI : public AbstractAI
{
public:
	RandomAI(Player* player);

protected:
	virtual void doTurn(float dt);

private:
	Hexagon* getRandomControlledHexagon();
	Hexagon* getRandomSideHexagon(Hexagon* hex);
};
