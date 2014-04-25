#pragma once

#include "Constants.h"
#include "Point.h"

class Player;
class Hexagon;

class PathsLayer : public CCLayer{
public:
    PathsLayer();
    virtual void draw();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
private:
    // startHex, endHex
    typedef std::map<Hexagon*, Hexagon*> TouchesContainer;
    
    // Player от которого идет тач начала и Point текущего положения тача
    TouchesContainer touchesBegan;
    // TODO если будут независимые выборы даже для одного игрока тут нужно хранить не игрока а начальный hexagon
    
    // сейчас от одного юзера только 1 набор путей
    
    
    void findAndRemoveTouches(CCSet *pTouches);
    
    // возвращает первый их начатых тачей
    Hexagon* getEndPointForUser(Player* player);
    
    void addTouch(Hexagon* startHex, Hexagon* endTouch);
    void removeTouch(Hexagon* startHex);
    
    // TODO вся эта логика должна еще создавать массив который будет рисоваться за 1 раз
    void drawArmies();
    void drawTouches();
    
    void drawPath(const std::list<Hexagon*>& path);
    void drawPlayersSelected(Player* player, Hexagon* endHex);
};

/*
    внутри touches move только наверное
    нужно определять куда он подвинулся и добавить эту информацию в отрисовку
    пока этот конкретный тач не закончится
 
    можно наверное хранить в зависимоти от начального хексагона?
    если бы можно было отрисовать в момент мува - было бы проще конечно? но чтобы осталось - не понятно
 
    мне нужно знать и конечную точку? так что добавляется и убирается только в тач муве наверное
    
 у меня щас выделения полностью зависимые вообщем-то так что про что я думаю то? мне в теории интересен только тач мув - который запишет кто и что - причем игнорировать когда несколько тачей от одного игрока пока?
 
    сами линии в теории должны как-то хранится в массиве - но они меняются постоянно кстати
    независимо должны хранится?
    мне нужна конечная точка - это точка хексагона над которым щас
    и мне нужны еще все точки начала
 
    к методам возможности определить такую информацию нужно дать доступ
    типо получить по тачу конкретный хексагон
    ну а получить все не сложно
 
 
 ///
    начальные точки уже получаются внутри отрисовки!!
 
 мне нужно только внутри touchmoev записывать точки конца для каждого игрока причем одна
 можно даже конечный текущий хексагон для того чтобы проще было
 
 ну полюбас
    потому что мне еще пути до него считать из каждой начальной точки!!!!!!!
 */