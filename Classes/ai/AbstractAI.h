#pragma once

#include "cocos2d.h"

const float defaultDelay = .75f;


class Player;
class AbstractAI : public cocos2d::CCNode
{
public:
    enum Type{
        NoAI,
        Conqueror,
        Expansion,
        Random,
        AI_COUNT,
        ErrorAI // if ai was null for example
    };
    
	AbstractAI(Type aiType, Player* player, float turnDelay = defaultDelay);
    virtual ~AbstractAI();
    
    static AbstractAI* create(Type type, Player* player);
    
    void unscheduleSelector();
    
    Type getType();

protected:
	Player* player;

	virtual void doTurn(float dt) = 0;

private:
	float turnDelay;
    Type aiType;
};


