#include "AbstractAI.h"
#include "../Player.h"



AbstractAI::AbstractAI(Type aiType, Player* player, float turnDelay): turnDelay(turnDelay), player(player), aiType(aiType)
{
	CCNode::init();

	// Note: позволяет сделать schedule даже если нод не добавлен как чилд
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AbstractAI::doTurn), this, turnDelay, false);
}

AbstractAI::~AbstractAI()
{
    unscheduleSelector();
}

void AbstractAI::unscheduleSelector()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(AbstractAI::doTurn),this);
}


AbstractAI::Type AbstractAI::getType()
{
    return aiType;
}