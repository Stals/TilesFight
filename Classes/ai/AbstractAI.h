#pragma once

#include "cocos2d.h"

class Player;
class AbstractAI : public cocos2d::CCNode
{
public:
	AbstractAI(Player* player);

protected:
	virtual void doTurn(float dt) = 0;

private:
	float turnDelay;

	Player* player;
};
