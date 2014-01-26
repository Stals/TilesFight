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
	
	virtual CCNode* getIcon();

	int getTroopsPerTick();
	// ‚ÓÁ‚‡˘‡ÂÚ ÒÍÓÎ¸ÍÓ ‰‡ÂÚÒˇ Á‡ ÚËÍ ‰Îˇ ÓÔÂ‰ÂÎÂÌÌÓ„Ó ÚËÔ‡ „ÂÌÂ‡ÚÓ‡
	static int getTroopsForType(GeneratorType type);

private:
    
	CCSprite* generatorIcon;
	int troopsPerTick;

	void tick(float dt);
};

