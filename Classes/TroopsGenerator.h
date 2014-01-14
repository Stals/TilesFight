#pragma once

#include "Hexagon.h"

enum GeneratorType{
	SmallGen, 
	MediumGen,
	LargeGen
};


class TroopsGenerator : public CCNode
{
public:
	TroopsGenerator(Hexagon* hex, GeneratorType type);
	~TroopsGenerator(void);
	
	CCSprite* getIcon();

	int getTroopsPerTick();

private:
	Hexagon* hex;

	CCSprite* generatorIcon;
	int troopsPerTick;

	void tick(float dt);
};

