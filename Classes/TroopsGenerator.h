#pragma once

#include "Addon.h"

enum GeneratorType{
	SmallGen, 
	MediumGen,
	LargeGen
};


class TroopsGenerator : public Addon
{
public:
	TroopsGenerator(Hexagon* hex, GeneratorType type);
	~TroopsGenerator(void);
	
	CCSprite* getIcon();

	int getTroopsPerTick();
	// возвращает сколько дается за тик для определенного типа генератора
	static int getTroopsForType(GeneratorType type);

private:
    
	CCSprite* generatorIcon;
	int troopsPerTick;

	void tick(float dt);
};

