#pragma once 

#include "cocos2d.h"

class ShakableSprite : public cocos2d::CCSprite{
public:
    ShakableSprite();
    void shake(float dt, float strength);

private:
    // true if is currently running shake action
    bool shaking;
    
    // called after shake action has ended - set shaking to false
    void endShake();
};