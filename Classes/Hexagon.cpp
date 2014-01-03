#include "Hexagon.h"

Hexagon::Hexagon(){
	initWithFile("image/hex.png");
	setColor(hexGray);
	
	autorelease();
}

void Hexagon::onEnter(){
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        CCSprite::onEnter();
}
void Hexagon::onExit(){
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        CCSprite::onExit();
}
bool Hexagon::ccTouchBegan(CCTouch* touch, CCEvent* event){
	if(containsTouchLocation(touch)){
		//setColor(ccc3(rand()%256, rand()%256, rand()%256));
		setColor(hexRed);
		return true;
	}
	return false;
}

void Hexagon::ccTouchMoved(CCTouch* touch, CCEvent* event){

}

void Hexagon::ccTouchEnded(CCTouch* touch, CCEvent* event){
	//if(containsTouchLocation(touch)){
		//setColor(ccc3(rand()%256, rand()%256, rand()%256));
	//}
}

bool Hexagon::containsTouchLocation(cocos2d::CCTouch *touch) {
	CCPoint point = touch->getLocation();
	point.x -= 64;
	point.y -= 48;
	//touch->
	return rect().containsPoint(point/*this->convertTouchToNodeSpaceAR(touch)*/);
}

CCRect Hexagon::rect() {
	CCRect c = CCRectMake(
                    (getPosition().x - (getTextureRect().size.width / 2) * getScaleX()),
                    (getPosition().y - (getTextureRect().size.height / 2)* getScaleY()),
                    getTextureRect().size.width * getScaleX(),
                    getTextureRect().size.height* getScaleY());
                                        
    return c;
}