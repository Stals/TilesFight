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
	if(ai) ai->unscheduleSelector();
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

void Player::setAI(AbstractAI::Type type)
{
    ai = AbstractAI::create(type, this);
}

void Player::setAI(AbstractAI* newAI)
{
	ai = newAI;
}

ccColor3B Player::getColor() const
{
	return color;
}

bool Player::isNeutral()
{
	return neutral;
}

bool Player::removeControlledHexagon(Hexagon* hex)
{
	controlledHexagons.erase(hex);
    
    // проверяем если на нем increaser - то уменьшаем troopsPerTick
    const Addon* addon = hex->getAddon();
    if(addon && (addon->getType() == Addon::AIncreaser)){
        troopsPerTick -= ((AmoutIncreaser*)addon)->getAdditionalAmout();
    }
    
    return false;
}

void Player::addControlledHexagon(Hexagon* hex)
{
	controlledHexagons.insert(hex);
    
    // проверяем если на нем increaser - то увеличивает troopsPerTick
    const Addon* addon = hex->getAddon();
    if(addon && (addon->getType() == Addon::AIncreaser)){
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
        if((*it)->getTroopsCount() > 0)
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

std::vector<Hexagon*> Player::getSelectedHexagons()
{
    std::vector<Hexagon*> result;
    
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        if((*it)->isSelected())
            result.push_back(*it);
    }
    
    return result;
}

void Player::setHexagonsSelected(bool selected)
{
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        (*it)->setSelected(selected);
    }
}

void Player::selectAllHexagons()
{
    for(std::set<Hexagon*>::iterator it = controlledHexagons.begin(); it != controlledHexagons.end(); ++ it)
    {
        if((*it)->isSelectable()){
            (*it)->setSelected(true);
        }
    }
}

void Player::deselectAllHexagons()
{
    setHexagonsSelected(false);
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

bool Player::isHexagonsSelectable()
{
    return !ai;
}

void Player::reset()
{
    troopsPerTick = TROOPS_PER_TICK;
    controlledHexagons.clear();
    
    // recreate ai
    if(ai){
        AbstractAI::Type type = ai->getType();
        delete ai;
        setAI(type);
    }
}


