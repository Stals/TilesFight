#include "NoAI.h"
#include "../Player.h"

NoAI::NoAI(Player* player):AbstractAI(player)
{
	// ������ schedule �.�. �������� ������ �� ������
	this->unscheduleSelector();
}

