#include "NoAI.h"
#include "../Player.h"

NoAI::NoAI(Player* player):AbstractAI(AbstractAI::NoAI, player)
{
	// ������ schedule �.�. �������� ������ �� ������
	this->unscheduleSelector();
}

