#include "TroopsGenerator.h"

#define TROOPS_PER_TICK 5


TroopsGenerator::TroopsGenerator(Hexagon* hex, GeneratorType type):Addon(hex), generatorIcon(0), troopsPerTick(0)
{
	float delay =  0.f;
	switch(type){
	case SmallGen:
		generatorIcon = CCSprite::create(IMG("smallGen.png"));
		delay = 5.f;
		break;
	case MediumGen:
		generatorIcon = CCSprite::create(IMG("mediumGen.png"));
		delay = 2.5f;
		break;
	case LargeGen:
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
		hex->addTroops(TROOPS_PER_TICK);
        
        const float maxScale = 1.1;//1 + 3 * (( 1 / dt ) / 10);
		hex->runScaleLabelAction(maxScale);
	}
}
