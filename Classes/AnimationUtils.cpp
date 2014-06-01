#include "AnimationUtils.h"


void AnimationUtils::playBlinkAnimation(cocos2d::CCSprite *sprite)
{
    CCTintTo* t1 = CCTintTo::create(0.1f, 255, 255, 255);
    ccColor3B color = sprite->getColor();
    CCTintTo* t2 = CCTintTo::create(0.2f, color.r, color.g, color.b);
    
    sprite->runAction(CCSequence::createWithTwoActions(t1, t2));
    
     /*
      ccColor3B* oldColor = new ccColor3B(
      
      sprite->setColor(ccc3(255, 255, 255));
      
      CCSequence::createWithTwoActions(CCDelayTime::, <#cocos2d::CCFiniteTimeAction *pActionTwo#>)
      
      sprite->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(_tiemToDelay),CCCallFunc::actionWithTarget(this,callfunc_selector(xxx::functionYouWant),NULL));
      */
}
