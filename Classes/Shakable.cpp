#include "Shakable.h"

#include "CCShake.h"

USING_NS_CC;

ShakableSprite::ShakableSprite():shaking(false)
{
}

void ShakableSprite::shake(float dt, float strength)
{
    if(shaking) return;

    CCEaseIn* shakeAction = CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt);
    CCFiniteTimeAction* endShakeFunc = CCCallFunc::create(this,callfunc_selector(ShakableSprite::endShake));
    CCSequence* seq = CCSequence::create(shakeAction, endShakeFunc, NULL);

    this->runAction(seq);
    shaking = true;
}

void ShakableSprite::endShake()
{
    shaking = false;
}