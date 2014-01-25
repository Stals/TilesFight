#include "AbstractAI.h"
#include "../Player.h"


const float defaultDelay = .75f;

AbstractAI::AbstractAI(Player* player): turnDelay(defaultDelay), player(player)
{
	CCNode::init();

	// Note: позволяет сделать schedule даже если нод не добавлен как чилд
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AbstractAI::doTurn),this,defaultDelay,false);
}

void AbstractAI::unscheduleSelector()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(AbstractAI::doTurn),this);
}
