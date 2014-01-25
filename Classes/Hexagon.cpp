#include "Hexagon.h"
#include "utils/StringExtension.h"
#include "TroopsGenerator.h"

Hexagon::Hexagon(size_t x_coord, size_t y_coord): 
	x_coord(x_coord), y_coord(y_coord), owner(0), troopsCount(0), 
	isSelected(false), selection(0), generator(0)
{
	initWithFile(IMG("hex3.png"));
	setColor(hexDefault);
	setOpacity(50);

	setupTroopsLabel();
	
	autorelease();
}

Hexagon::~Hexagon()
{
	//if(generator) delete generator;
}

size_t Hexagon::getXCoord()
{
	return x_coord;
}

size_t Hexagon::getYCoord()
{
	return y_coord;
}

int Hexagon::getTroopsCount()
{
	return troopsCount;
}

void Hexagon::removeTroops(int troops)
{
	troopsCount -= troops;
	if(troopsCount > 0){
		troopsLabel->setString(StringExtension::toString(troopsCount).c_str());
	}else{
		troopsLabel->setString("");
	}
}

void Hexagon::addTroops(int troops)
{
	// TODO вызуально показать что добавилось и зафейдить
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

	// Note: это нужно если игроки ровно убились, и клетка осталась без хоз€ина
	if(owner){
		setColor(owner->getColor());
		setOpacity(220);
	}else{
		setColor(hexDefault);
		setOpacity(50);
	}
}


void Hexagon::changeOwner(Player* newOwner)
{
	if(owner) owner->removeControlledHexagon(this);
	setOwner(newOwner);
	if(newOwner) newOwner->addControlledHexagon(this);
}

void Hexagon::setSelected(bool selected)
{
	if(!getOwner()) return;

	if(!selection){
		selection = CCSprite::create(IMG("hex_glow3.png"));
		selection->setPosition(ccp((getTextureRect().size.width / 2)  , (getTextureRect().size.height / 2)  ));
		this->addChild(selection, zSelectionGlow);
	}

	this->isSelected = selected;
	selection->setVisible(isSelected);
}

void Hexagon::toggleSelected()
{
	setSelected(!isSelected);
}

void Hexagon::setGenerator(TroopsGenerator* generator)
{
	this->generator = generator;

	generatorIcon = generator->getIcon();
	//genIcon->getTexture()->setAliasTexParameters();
	//genIcon->setScale(0.6f);
	generatorIcon->setPosition(ccp((getTextureRect().size.width)  / 2, (getTextureRect().size.height) / 1.35f));
	this->addChild(generatorIcon, zGenIcon);
	this->addChild(generator);
}

bool Hexagon::hasGenerator()
{
    return generator;
}

void Hexagon::runScaleAction()
{
	CCEaseInOut* action1 = CCEaseInOut::create(CCScaleTo::create(0.1f, 0.30f, 0.30f), 2.f);
	CCEaseInOut* action2 = CCEaseInOut::create(CCScaleTo::create(0.5f, 0.25f, 0.25f), 2.f);
	CCSequence* seq = CCSequence::create(action1, action2, NULL);
	
	this->runAction(seq);
}

void Hexagon::runScaleLabelAction(float maxScale)
{
	CCEaseInOut* action1 = CCEaseInOut::create(CCScaleTo::create(0.1f, maxScale, maxScale), 2.f);
	CCEaseInOut* action2 = CCEaseInOut::create(CCScaleTo::create(0.5f, 1.f, 1.f), 2.f);
	CCSequence* seq = CCSequence::create(action1, action2, NULL);

	troopsLabel->runAction(seq);
}

void Hexagon::setupTroopsLabel()
{
	troopsLabel = CCLabelTTF::create("", default_font.c_str(), 64);
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
	// там в комментари€х есть пример дл€ перевернутого тоже
	//const double offset = 3; // - TODO им нужно мен€ть vert и hori

	const double _vert = ((getTextureRect().size.width) * getScaleX()) / 4;
	const double _hori = ((getTextureRect().size.width) * getScaleX()) / 2;

	const double q2x = fabs(pos.x - getPosition().x);         // transform the test point locally and to quadrant 2
    const double q2y = fabs(pos.y - getPosition().y);         // transform the test point locally and to quadrant 2
    if (q2x > _hori || q2y > _vert*2) return false;           // bounding test (since q2 is in quadrant 2 only 2 tests are needed)
    return 2 * _vert * _hori - _vert * q2x - _hori * q2y >= 0;   // finally the dot product can be reduced to this due to the hexagon symmetry
}
