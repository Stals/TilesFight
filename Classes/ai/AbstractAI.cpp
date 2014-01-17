#include "AbstractAI.h"
#include "../Player.h"


const float defaultDelay = 2.5f;

AbstractAI::AbstractAI(Player* player): turnDelay(defaultDelay), player(player)
{
	this->schedule( schedule_selector(AbstractAI::doTurn), defaultDelay );
}
