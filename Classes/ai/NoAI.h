#pragma once

#include "AbstractAI.h"

// AI ������� ������ �� ������
class NoAI : public AbstractAI{
public:
	NoAI(Player* player);

	void doTurn(float dt){
	}
};
