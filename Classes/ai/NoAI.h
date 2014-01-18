#pragma once

#include "AbstractAI.h"

// AI который ничего не делает
class NoAI : public AbstractAI{
public:
	NoAI(Player* player);

	void doTurn(float dt){
	}
};
