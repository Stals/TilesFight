#include "Hexagon.h"
#include "utils/StringExtension.h"
#include "Addons/TroopsGenerator.h"
#include "Army.h"

Hexagon::Hexagon(size_t x_coord, size_t y_coord): 
	x_coord(x_coord), y_coord(y_coord), owner(0), troopsCount(0), 
	selected(false), selection(0), addon(0)
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

size_t Hexagon::getXCoord() const
{
	return x_coord;
}

size_t Hexagon::getYCoord() const
{
	return y_coord;
}

Point Hexagon::getCoord() const
{
    return Point(x_coord, y_coord);
}


int Hexagon::getTroopsCount()
{
	return troopsCount;
}

void Hexagon::removeTroops(int troops)
{
	troopsCount -= troops;
	if(troopsCount > 0){
        troopsLabel->setString(StringExtension::toString(getTroopsCount()).c_str());
	}else{
		troopsLabel->setString("");
	}
}

void Hexagon::addTroops(int troops)
{
	// TODO ‚˚ÁÛ‡Î¸ÌÓ ÔÓÍ‡Á‡Ú¸ ˜ÚÓ ‰Ó·‡‚ËÎÓÒ¸ Ë Á‡ÙÂÈ‰ËÚ¸
	troopsCount += troops;
	troopsLabel->setString(StringExtension::toString(getTroopsCount()).c_str());
}

Player* Hexagon::getOwner()
{
	return owner;
}

void Hexagon::setOwner(Player* owner)
{
	this->owner = owner;

	// Note: ˝ÚÓ ÌÛÊÌÓ ÂÒÎË Ë„ÓÍË Ó‚ÌÓ Û·ËÎËÒ¸, Ë ÍÎÂÚÍ‡ ÓÒÚ‡Î‡Ò¸ ·ÂÁ ıÓÁˇËÌ‡
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
    // TODO если я выигрываю когда у меня выделено больше чем 1  - то вылетит!
	if(owner) owner->removeControlledHexagon(this);
    setOwner(newOwner);
	if(newOwner) newOwner->addControlledHexagon(this);
}

bool Hexagon::isSelected()
{
    return selected;
}


void Hexagon::setSelected(bool selected)
{
	if(!getOwner()) return;

	if(!selection){
		selection = CCSprite::create(IMG("hex_glow3.png"));
		selection->setPosition(ccp((getTextureRect().size.width / 2)  , (getTextureRect().size.height / 2)  ));
		this->addChild(selection, zSelectionGlow);
	}

	this->selected = selected;
	selection->setVisible(selected);
}

void Hexagon::toggleSelected()
{
	setSelected(!selected);
}

void Hexagon::setAddon(Addon* addon)
{
	this->addon = addon;

	addonIcon = addon->getIcon();
	//genIcon->getTexture()->setAliasTexParameters();
	//genIcon->setScale(0.6f);
	addonIcon->setPosition(ccp((getTextureRect().size.width)  / 2, (getTextureRect().size.height) / 1.35f));
	this->addChild(addonIcon, zGenIcon);
	this->addChild(addon);
}

bool Hexagon::hasAddon()
{
    return addon;
}

const Addon* Hexagon::getAddon()
{
    return addon;
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



Army* Hexagon::createArmy(Point destination)
{
    float factor = 1.0f; // player->getPecent() / 100;
    
    int troops = troopsCount * factor;
    if(troops == troopsCount) troops -= 1;
    
    removeTroops(troops);
    return new Army(this, troops, destination);
}

void Hexagon::removeArmy(Army* army)
{
    armies.remove(army);
    troopsLabel->setString(StringExtension::toString(getTroopsCount()).c_str());
}

void Hexagon::addArmy(Army *army)
{
    armies.push_back(army);
    troopsLabel->setString(StringExtension::toString(getTroopsCount()).c_str());
}


// --------------TOUCH----------------------
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
	// Ú‡Ï ‚ ÍÓÏÏÂÌÚ‡Ëˇı ÂÒÚ¸ ÔËÏÂ ‰Îˇ ÔÂÂ‚ÂÌÛÚÓ„Ó ÚÓÊÂ
	//const double offset = 3; // - TODO ËÏ ÌÛÊÌÓ ÏÂÌˇÚ¸ vert Ë hori

	const double _vert = ((getTextureRect().size.width) * getScaleX()) / 4;
	const double _hori = ((getTextureRect().size.width) * getScaleX()) / 2;

	const double q2x = fabs(pos.x - getPosition().x);         // transform the test point locally and to quadrant 2
    const double q2y = fabs(pos.y - getPosition().y);         // transform the test point locally and to quadrant 2
    if (q2x > _hori || q2y > _vert*2) return false;           // bounding test (since q2 is in quadrant 2 only 2 tests are needed)
    return 2 * _vert * _hori - _vert * q2x - _hori * q2y >= 0;   // finally the dot product can be reduced to this due to the hexagon symmetry
}
