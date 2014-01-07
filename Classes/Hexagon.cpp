#include "Hexagon.h"
#include "StringExtension.h"

Hexagon::Hexagon(): troopsCount(0)
{
	initWithFile("image/hex.png");
	setColor(hexGray);

	setupTroopsLabel();
	
	autorelease();
}

int Hexagon::getTroopsCount()
{
	return troopsCount;
}

void Hexagon::addTroops(int troops)
{
	// TODO вызуально показать что добавилось и зафейдить
	troopsCount += troops;
	troopsLabel->setString(StringExtension::toString(troopsCount).c_str());
}

void Hexagon::setupTroopsLabel()
{
	troopsLabel = CCLabelTTF::create("", "fonts/GAMECUBEN.ttf", 64);
	troopsLabel->setPosition(ccp((getTextureRect().size.width) * getScaleX() / 2, (getTextureRect().size.height) * getScaleY() / 2));

	this->addChild(troopsLabel);
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
