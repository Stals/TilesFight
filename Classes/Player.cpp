#include "Player.h"
#include "Hexagon.h"
#include "ai/AbstractAI.h"
#include "Addons/AmoutIncreaser.h"

#define TROOPS_PER_TICK 5


Player::Player(const std::string &name, const ccColor3B& color): 
	name(name), color(color), ai(0), neutral(false), troopsPerTick(TROOPS_PER_TICK)
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
    
    // проверяем если на нем increaser - то уменьшаем troopsPerTick
    const Addon* addon = hex->getAddon();
    if(addon && (addon->getType() == AIncreaserAddon)){
        troopsPerTick -= ((AmoutIncreaser*)addon)->getAdditionalAmout();
    }

    if((!isNeutral()) && hasLost())
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(PLAYER_LOOSE_MGS.c_str(), this);
}

void Player::addControlledHexagon(Hexagon* hex)
{
	controlledHexagons.insert(hex);
    
    // проверяем если на нем increaser - то увеличивает troopsPerTick
    const Addon* addon = hex->getAddon();
    if(addon && (addon->getType() == AIncreaserAddon)){
        troopsPerTick += ((AmoutIncreaser*)addon)->getAdditionalAmout();
    }
}

std::set<Hexagon*>& Player::getControlledHexagons()
{
	return controlledHexagons;
}

std::vector<Hexagon*> Player::getHexagonsWithTroops()
{
    std::vector<Hexagon*> result;
    
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        if((*it)->getTroopsCount() > 1)
            result.push_back(*it);
    }
    
    return result;
}

std::vector<Hexagon*> Player::getHaxagonsWithGenerators()
{
    std::vector<Hexagon*> result;
    
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        if((*it)->hasAddon())
            result.push_back(*it);
    }
    
    return result;
}

bool Player::hasLost()
{
    if(controlledHexagons.size() == 0) return true;
    
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        Hexagon* hex = *it;
        
        if(hex->hasAddon() || (hex->getTroopsCount() > 1)){
            return false;
        }
    }
    return true;
}

int Player::getTroopsPerTick()
{
    return troopsPerTick;
}


