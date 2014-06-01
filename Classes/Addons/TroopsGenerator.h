#pragma once

#include "Addon.h"




class TroopsGenerator : public Addon
{
public:
    enum Type{
        Small,
        Medium,
        Large
    };
    
	TroopsGenerator(Hexagon* hex, TroopsGenerator::Type type);
	~TroopsGenerator(void);
	
	virtual CCSprite* getIcon();

	int getTroopsPerTick();
	// ‚ÓÁ‚‡˘‡ÂÚ ÒÍÓÎ¸ÍÓ ‰‡ÂÚÒˇ Á‡ ÚËÍ ‰Îˇ ÓÔÂ‰ÂÎÂÌÌÓ„Ó ÚËÔ‡ „ÂÌÂ‡ÚÓ‡
	static int getTroopsForType(TroopsGenerator::Type type);

private:
    
	CCSprite* generatorIcon;
	int troopsPerTick;

	void tick(float dt);
};

