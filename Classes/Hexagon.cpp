#include "Hexagon.h"

Hexagon::Hexagon(){
	initWithFile("image/hex.png");
	setColor(hexGray);
	
	autorelease();
}


bool Hexagon::containsTouchLocation(cocos2d::CCTouch *touch) {
	return rect().containsPoint(getParent()->convertTouchToNodeSpace(touch));
}

CCRect Hexagon::rect() {
	CCRect c = CCRectMake(
                    (getPosition().x - (getTextureRect().size.width / 2) * getScaleX()),
                    (getPosition().y - (getTextureRect().size.height / 2)* getScaleY()),
                    getTextureRect().size.width * getScaleX(),
                    getTextureRect().size.height* getScaleY());
                                        
    return c;
}