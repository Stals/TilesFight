#pragma once

#include "cocos2d.h"

const float defaultDelay = .75f;


class Player;
class AbstractAI : public cocos2d::CCNode
{
public:
	AbstractAI(Player* player, float turnDelay = defaultDelay);
    virtual ~AbstractAI();
    
    void unscheduleSelector();

protected:
	Player* player;

	virtual void doTurn(float dt) = 0;

private:
	float turnDelay;
};
