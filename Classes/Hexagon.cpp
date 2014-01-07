#include "Hexagon.h"

Hexagon::Hexagon(){
	initWithFile("image/hex.png");
	setColor(hexGray);
	
	autorelease();
}


bool Hexagon::containsTouchLocation(cocos2d::CCTouch *touch) {
	CCPoint pos = getParent()->convertTouchToNodeSpace(touch);

	// http://www.playchilla.com/how-to-check-if-a-point-is-inside-a-hexagon
	// там в комментариях есть пример для перевернутого тоже
	//const double offset = 3;

	const double _vert = ((getTextureRect().size.width) * getScaleX()) / 4;
	const double _hori = ((getTextureRect().size.width) * getScaleX()) / 2;

	const double q2x = fabs(pos.x - getPosition().x);         // transform the test point locally and to quadrant 2
    const double q2y = fabs(pos.y - getPosition().y);         // transform the test point locally and to quadrant 2
    if (q2x > _hori || q2y > _vert*2) return false;           // bounding test (since q2 is in quadrant 2 only 2 tests are needed)
    return 2 * _vert * _hori - _vert * q2x - _hori * q2y >= 0;   // finally the dot product can be reduced to this due to the hexagon symmetry
}

CCRect Hexagon::rect() {
	CCRect c = CCRectMake(
                    (getPosition().x - (getTextureRect().size.width / 2) * getScaleX()),
                    (getPosition().y - (getTextureRect().size.height / 2)* getScaleY()),
                    getTextureRect().size.width * getScaleX(),
                    getTextureRect().size.height* getScaleY());
                                        
    return c;
}