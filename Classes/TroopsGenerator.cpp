#include "TroopsGenerator.h"

#define TICK_DELAY 5.f // seconds

TroopsGenerator::TroopsGenerator(Hexagon* hex, GeneratorType type): hex(hex), generatorIcon(0), troopsPerTick(0)
{
	CCNode::init();


	float delay =  0.f;
	switch(type){
	case SmallGen:
		generatorIcon = CCSprite::create("image/smallGen.png");
		delay = 5.f;
		break;
	case MediumGen:
		generatorIcon = CCSprite::create("image/mediumGen.png");
		delay = 2.5f;
		break;
	case LargeGen:
		generatorIcon = CCSprite::create("image/largeGen.png");
		delay = 1.f;
		break;
	}
	troopsPerTick = getTroopsForType(type);

	this->schedule( schedule_selector(TroopsGenerator::tick), delay );
}


TroopsGenerator::~TroopsGenerator(void)
{
}
	
CCSprite* TroopsGenerator::getIcon()
{
	return generatorIcon;
}

int TroopsGenerator::getTroopsPerTick()
{
	return troopsPerTick;
}

int TroopsGenerator::getTroopsForType(GeneratorType type)
{
	switch(type){
	case SmallGen:
		return 5;
	case MediumGen:
		return 10;
	case LargeGen:
		return 25;
	}
}


void TroopsGenerator::tick(float dt)
{
	if(hex->getOwner() && (!hex->getOwner()->isNeutral())){
		hex->addTroops(5);
		hex->runScaleLabelAction();
	}
}
