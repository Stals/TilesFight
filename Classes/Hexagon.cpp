#include "Hexagon.h"
#include "StringExtension.h"

Hexagon::Hexagon(): owner(0), troopsCount(0), isSelected(false)
{
	initWithFile("image/hex.png");
	setColor(hexDefault);

	setupTroopsLabel();
	
	autorelease();
}

int Hexagon::getTroopsCount()
{
	return troopsCount;
}

void Hexagon::removeTroops(int troops)
{
	troopsCount -= troops;
	troopsLabel->setString(StringExtension::toString(troopsCount).c_str());
}

void Hexagon::addTroops(int troops)
{
	// TODO ��������� �������� ��� ���������� � ���������
	troopsCount += troops;
	troopsLabel->setString(StringExtension::toString(troopsCount).c_str());
}

Player* Hexagon::getOwner()
{
	return owner;
}

void Hexagon::setOwner(Player* owner)
{
	this->owner = owner;
	setColor(owner->getColor());
}

void Hexagon::setSelected(bool selected)
{
	CCSprite *selection = CCSprite::create("image/hex_glow3.png");

	selection->setPosition(ccp((getTextureRect().size.width / 2)  , (getTextureRect().size.height / 2)  ));
	this->addChild(selection, zSelectionGlow);

	/*

	this->isSelected = selected;

	if(selected){
		setColor(hexWhite);
	}else{
		if(owner){
			setColor(owner->getColor());
		}else{
			setColor(hexDefault);
		}
	}*/
}

void Hexagon::toggleSelected()
{
	setSelected(!isSelected);
}

void Hexagon::setupTroopsLabel()
{
	troopsLabel = CCLabelTTF::create("", "fonts/GAMECUBEN.ttf", 64);
	troopsLabel->setPosition(ccp((getTextureRect().size.width) * getScaleX() / 2, (getTextureRect().size.height) * getScaleY() / 2));

	this->addChild(troopsLabel, zTroopsCount);
}


bool Hexagon::containsTouchLocation(cocos2d::CCTouch *touch) {
	return containsPoint(getParent()->convertTouchToNodeSpace(touch));
}

bool Hexagon::containsTouchLocation(cocos2d::CCPoint point)
{
	return containsPoint(getParent()->convertToNodeSpace(point));
}

bool Hexagon::containsPoint(cocos2d::CCPoint pos)
{
	// http://www.playchilla.com/how-to-check-if-a-point-is-inside-a-hexagon
	// ��� � ������������ ���� ������ ��� ������������� ����
	//const double offset = 3; // - TODO �� ����� ������ vert � hori

	const double _vert = ((getTextureRect().size.width) * getScaleX()) / 4;
	const double _hori = ((getTextureRect().size.width) * getScaleX()) / 2;

	const double q2x = fabs(pos.x - getPosition().x);         // transform the test point locally and to quadrant 2
    const double q2y = fabs(pos.y - getPosition().y);         // transform the test point locally and to quadrant 2
    if (q2x > _hori || q2y > _vert*2) return false;           // bounding test (since q2 is in quadrant 2 only 2 tests are needed)
    return 2 * _vert * _hori - _vert * q2x - _hori * q2y >= 0;   // finally the dot product can be reduced to this due to the hexagon symmetry
}
