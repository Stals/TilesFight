#pragma once

#include <list>

#include "Constants.h"
#include "Hexagon.h"
#include "HexArray.h"
#include "TroopsMover.h"


struct LinesData{
    //LinesData(){}
    
    std::vector<CCPoint> starts;
    CCPoint end;
};

/*
 
 Для каждого игрка есть массив кнопок конца (тачи)
 Пока для одного игрока наверное мультитач сложно сделать нужно помнить каким тачем он именно что начал собирать
 и все выделенные хексагоны этим именно тачем будует начальными точками а сам тач конечной
 
 
 Тогда пока мне нужно только много начальных и 1 end для всех игроков
 
 */


class Board : public CCLayer{
public:
	Board(int width, int height);
    ~Board();

	Hexagon* at(size_t x, size_t y);
	Hexagon* sideHexAt(HexSide side, size_t x, size_t y);
    Hexagon* sideHexAt(HexSide side, Hexagon* hex);
    
    std::list<Hexagon*> getPath(Hexagon* start, Hexagon* end);



	int getWidth(size_t row);
	int getHeight();
    
    
private:
	int width, height;
	HexArray2D hexArray2D;
    std::map<Player*, LinesData> lines;

	void initBoard();

	void getStartEndHex(CCTouch* touch, Hexagon*& startHex, Hexagon*& endHex);	
	
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void draw();
    
    void addLine(Player* player, const CCPoint &start);
    void clearLines();
    void setEndPoint(Player* player, const CCPoint& endPoint);
};

// TODO
/*
	ÃÓÊÂÚ ı‡ÌÂÌËÂ Ë ‰ÓÒÚÛÔ ‚˚ÌÂÒÚË Â˘Â?
	ˇ ‰ÛÏ‡˛ ‰‡, ÚÓ„‰‡ ÔË ‰Ó·‡‚ÎÂÌËË ·Û‰ÂÚ ËÁË. ÌÓ ‚ÌÛÚË Ú‡Ï ·Û‰ÂÚ Á‡ÏÂÒ ÔÓËÒıÓ‰ËÚ¸ =)
	 ‡Í Ì‡Á‚‡Ú¸, Í‡Í ı‡ÌËÚ¸?

	—ÓÁ‰‡Ú¸ ˇ ‰ÛÏ‡˛ ÒÓÁ‰‡‚‡Ú¸ Ò‡ÁÛ ˜ÂÂÁ N ÚËÔÓ ÒÍÓÎ¸ÍÓ ‚ ÒÚÓÍÂ?
	’ÓÚˇ ÌÂÚ.
	œÓÒÚÓ ÒÏÓÚˇ Ì‡ ÍÓÎË˜ÂÒÚ‚Ó ÒÚÓÍ ÓÌ ·Û‰ÂÚ Ò Ô‡‚ËÎ¸Ì˚Ï ÒÏÂ˘ÂÌËÂÏ ÛÊÂ ‰Ó·‡‚ÎˇÚ¸?
	ÚÓ„‰‡ ÏÌÂ ÌÛÊÌÓ Á‡‡ÌËÂ ÁÌ‡Ú¸?
	ÀË·Ó Ú‡Ï ·˚ÎÓ Í‡Í Á‡ÌËÚ¸ ·ÂÁ ÒÏÂ˘ÂÌËÈ? ˇ ÌÂ Û‚ÂÂÌ

	HexArray
*/