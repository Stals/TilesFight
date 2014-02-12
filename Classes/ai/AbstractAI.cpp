#include "AbstractAI.h"
#include "../Player.h"



AbstractAI::AbstractAI(Player* player, float turnDelay): turnDelay(turnDelay), player(player)
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
