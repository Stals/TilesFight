#pragma once
#include "AbstractAI.h"

class RandomAI : public AbstractAI
{
public:
	RandomAI(Player* player);

protected:
	virtual void doTurn(float dt);
};
