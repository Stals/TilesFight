#pragma once

#include "cocos2d.h"

class ClippingSprite : public cocos2d::CCLayer
{
public:
    ClippingSprite();
    ~ClippingSprite();

    // used openGL for restrict area
    virtual void visit();
    //    virtual void draw(void);
    // set restrict region (to clippingRegion)
    void setClippingRegion(const cocos2d::CCRect& region);
    virtual cocos2d::CCSize& getContentSize();
	static void setHardScissor(bool hardScissor);

private:
    //rect for restrict layer
    cocos2d::CCRect clippingRegion;
    cocos2d::CCPoint p1, p2;

    int rect[4];
    cocos2d::CCPoint begin, end;
	//set true to scissor even if clippingRegion off-screen
	static bool _hardScissor;
};
