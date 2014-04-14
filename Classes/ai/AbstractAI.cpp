#include "AbstractAI.h"
#include "../Player.h"

#include "NoAI.h"
#include "ConquerorAI.h"
#include "ExpansionAI.h"
#include "RandomAI.h"


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

AbstractAI* AbstractAI::create(Type type, Player* player)
{
    /*
     NoAI,
     Conqueror,
     Expansion,
     Random,
     */
    
    switch (type) {
        case AbstractAI::Conqueror:
            return new ConquerorAI(player);
            
        case AbstractAI::Expansion:
            return new ExpansionAI(player);
            
        case AbstractAI::Random:
            return new RandomAI(player);
            
        case AbstractAI::NoAI:
        default:
            return new class NoAI(player);
    }
}
