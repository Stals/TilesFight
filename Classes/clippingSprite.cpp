#include "clippingSprite.h"

USING_NS_CC;

bool ClippingSprite::_hardScissor = false;

ClippingSprite::ClippingSprite()
{
    CCLayer::init();
    this->autorelease();
}

ClippingSprite::~ClippingSprite()
{
}

//overridden from CCNode, set openGL drawing rect
void ClippingSprite::visit()
{
    //CCLayer::visit();
    
    bool on = glIsEnabled(GL_SCISSOR_TEST);
    glGetIntegerv(GL_SCISSOR_BOX, rect);
    
    if(!on)
        glEnable(GL_SCISSOR_TEST);
   
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //glScissor used global coords, so convert them

    //int surf = s3eSurfaceGetInt( S3E_SURFACE_DEVICE_BLIT_DIRECTION );


    begin = convertToWorldSpace(p1);
    end   = convertToWorldSpace(p2);

    int w = static_cast<int>(floor((end.x - begin.x) + 0.5f));
    int h = static_cast<int>(floor((end.y - begin.y) + 0.5f));
    /// if (surf == S3E_SURFACE_BLIT_DIR_ROT270)
    /// {
    ///    float y1 = size.height - begin.y;
    ///    float y2 = size.height - end.y;
    ///    begin.y = y2;
    ///    end.y = y1;
    /// }
    //
    //
    //    CCLog("%i %i %i %i", (int)begin.x, (int)begin.y, h, w);
    //    CCLog("%i %i %i", surf, S3E_SURFACE_BLIT_DIR_ROT90, S3E_SURFACE_BLIT_DIR_ROT270);
    //restricting all but specified rect
    //if(!on)
    
    
    if(!on)
    {
        glScissor(static_cast<int>(floor(begin.x + 0.5f)),
                  static_cast<int>(floor(begin.y + 0.5f)), w, h);
    }
    else
    {
        CCRect cRect(static_cast<int>(floor(begin.x + 0.5f)),static_cast<int>(floor(begin.y + 0.5f)),w,h);
        CCRect cRect2(rect[0], rect[1], rect[2], rect[3]);
        
		//when clipping sprite is not in screen it must clip visible sprite on the screen
		//this "if" leads to not clipping properly sprites with slipping region outside the screen

        if(_hardScissor || cRect.intersectsRect(cRect2))
        {
            glScissor(static_cast<int>(floor(begin.x + 0.5f)),
                      static_cast<int>(floor(begin.y + 0.5f)), w, h);
        }
    }
    
    CCLayer::visit();
   
    if(!on)
        glDisable(GL_SCISSOR_TEST);
    else
        glScissor(rect[0], rect[1], rect[2], rect[3]);
}

//set new clipping region
void ClippingSprite::setClippingRegion(const CCRect& region)
{
    clippingRegion = region;
    p1 = ccp(clippingRegion.origin.x, 
             clippingRegion.origin.y);
    p2 = ccp(clippingRegion.origin.x + clippingRegion.size.width,
             clippingRegion.origin.y + clippingRegion.size.height);

}

cocos2d::CCSize& ClippingSprite::getContentSize()
{
    return clippingRegion.size;
}

void ClippingSprite::setHardScissor(bool hardScissor)
{
	_hardScissor = hardScissor;
}