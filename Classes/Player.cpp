#include "Player.h"

Player::Player(const std::string &name, const ccColor3B& color, bool ai): 
	name(name), color(color), ai(ai), neutral(false)
{
}

Player* Player::createNeutral()
{
	Player* player = new Player("neutral", hexDefault, true);
	player->neutral = true;
	return player;
}

std::string Player::getName()
{
	return name;
}

bool Player::isAI()
{
	return ai;
}

ccColor3B Player::getColor()
{
	return color;
}

bool Player::isNeutral()
{
	return neutral;
}
