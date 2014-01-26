#ifndef __SHAKE_H__
#define __SHAKE_H__

#include "cocos2d.h"

//#include "CCActionInterval.h"
using namespace cocos2d;


//TODO есть баг при котором если во время shake начнется еще один - то он все сломает
// Нужно проверять что shake уже есть и обновлять duration просто
class CCShake : public cocos2d::CCActionInterval
{
    // Code by Francois Guibert
public:
    CCShake();
    
    // Create the action with a time and a strength (same in x and y)
    static CCShake* actionWithDuration(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static CCShake* actionWithDuration(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
protected:
    // Initial position of the shaked node
    float _initial_x, _initial_y;
    // Strength of the action
    float _strength_x, _strength_y;
};

#endif //__SHAKE_H__