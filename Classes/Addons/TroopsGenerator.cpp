#include "TroopsGenerator.h"

#include "Hexagon.h"


TroopsGenerator::TroopsGenerator(Hexagon* hex, TroopsGenerator::Type type):Addon(hex, Addon::Generator), generatorIcon(0), troopsPerTick(0)
{
	float delay =  0.f;
	switch(type){
	case Small:
		generatorIcon = CCSprite::create(IMG("smallGen.png"));
		delay = 5.f;
		break;
	case Medium:
		generatorIcon = CCSprite::create(IMG("mediumGen.png"));
		delay = 2.5f;
		break;
	case Large:
		generatorIcon = CCSprite::create(IMG("largeGen.png"));
		delay = 1.f;
		break;
	}
	troopsPerTick = getTroopsForType(type);

	this->schedule( schedule_selector(TroopsGenerator::tick), delay );
}


TroopsGenerator::~TroopsGenerator(void)
{
}
	
CCNode* TroopsGenerator::getIcon()
{
	return generatorIcon;
}

int TroopsGenerator::getTroopsPerTick()
{
	return troopsPerTick;
}

int TroopsGenerator::getTroopsForType(TroopsGenerator::Type type)
{
	switch(type){
	case Small:
		return 5;
	case Medium:
		return 10;
	case Large:
		return 25;
	}
}


void TroopsGenerator::tick(float dt)
{
	if(hex->getOwner() && (!hex->getOwner()->isNeutral())){
		hex->addTroops(hex->getOwner()->getTroopsPerTick());
        
        const float maxScale = 1.1;//1 + 3 * (( 1 / dt ) / 10);
		hex->runScaleLabelAction(maxScale);
	}
}
