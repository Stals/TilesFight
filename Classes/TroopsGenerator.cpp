#include "TroopsGenerator.h"

#define TICK_DELAY 5.f // seconds

TroopsGenerator::TroopsGenerator(Hexagon* hex, GeneratorType type): hex(hex), generatorIcon(0), troopsPerTick(0)
{
	CCNode::init();

	switch(type){
	case SmallGen:
		troopsPerTick = 5;
		generatorIcon = CCSprite::create("image/smallGen.png");
		break;
	case MediumGen:
		troopsPerTick = 10;
		generatorIcon = CCSprite::create("image/mediumGen.png");
		break;
	case LargeGen:
		troopsPerTick = 25;
		generatorIcon = CCSprite::create("image/largeGen.png");
		break;
	}
	this->schedule( schedule_selector(TroopsGenerator::tick), TICK_DELAY );
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


void TroopsGenerator::tick(float dt)
{
	if(hex->getOwner() && (!hex->getOwner()->isNeutral())){
		hex->addTroops(troopsPerTick);
	}
}
