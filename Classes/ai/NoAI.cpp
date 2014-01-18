#include "NoAI.h"
#include "../Player.h"

NoAI::NoAI(Player* player):AbstractAI(player)
{
	// снимем schedule т.к. всеравно ничего не делаем
	this->unscheduleSelector();
}

