#include "Player.h"
#include "Hexagon.h"
#include "ai/AbstractAI.h"

Player::Player(const std::string &name, const ccColor3B& color): 
	name(name), color(color), ai(0), neutral(false)
{
}

Player::~Player()
{
	if(ai) delete ai;
}

Player* Player::createNeutral()
{
	Player* player = new Player("neutral", hexGray);
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

void Player::setAI(AbstractAI* newAI)
{
	ai = newAI;
}

ccColor3B Player::getColor()
{
	return color;
}

bool Player::isNeutral()
{
	return neutral;
}

void Player::removeControlledHexagon(Hexagon* hex)
{
	controlledHexagons.erase(hex);
}

void Player::addControlledHexagon(Hexagon* hex)
{
	controlledHexagons.insert(hex);
}

std::set<Hexagon*>& Player::getControlledHexagons()
{
	return controlledHexagons;
}

