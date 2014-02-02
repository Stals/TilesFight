#pragma once

#include "cocos2d.h"

class Player;
class AbstractAI : public cocos2d::CCNode
{
public:
	AbstractAI(Player* player);
    virtual ~AbstractAI();

protected:
	Player* player;

	virtual void doTurn(float dt) = 0;
	void unscheduleSelector();

private:
	float turnDelay;
};
