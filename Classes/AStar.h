// TODO в тоерии можно сделать 2d array с нодами и списком нодов созданный пир старте
// и потом он по координатам будет брать именно от сюда


// чтобы просто на каждый поиск не создавать заново ноды и не удалять их потом что просто лишние операции если считать что карата у меня всеравно не будет меняться
// Ну а этот Pathfinding лежит внутри board и так создается!!

// Это сделать как второй шаг
/*
 ОПТИМИЗАЦИЯ (чтобы не пересоздавать ноды)
 
 Еще раз короткое описание
 Board  создает AStart класс передавая туда себя
 Конструктор AStart создает 2d array с совпадающими координатами где каждый элмемент это нод
 и в нем лежат все его окружающие ноды
 тут нужно как-то определят что если нода уже создаана то лезть в дургое место?
 либо можно создать все ноды а потом добавить их соседей каждому - так наверное лучше
 причем если нода наследуется от Hexagon то можно это делать прям внутри hexArray2d!!
 
 */


#pragma once
#include <list>

#include "Hexagon.h"
#include "../lib/utils/StringExtension.h"

class Node;

class AStar{
public:
	AStar();
	~AStar();
    
	std::list<Hexagon*> findPath(Hexagon* startHex, Hexagon* endHex);

private:
	std::list<Node*> open;
	std::list<Node*> closed;
    
	Node* getBestNodeFromOpen();
    
	void removeFromOpen(Node* node);
    
	Node* isInOpen(Hexagon* hex);
	bool isInClosed(Hexagon* hex);
    
	std::list<Hexagon*> getPath(Node* finalNode);
    
    double hex_distance(Hexagon* hex1, Hexagon* hex2);
    double hex_distance(int q1, int r1, int q2, int r2);
};


class Node{
public:
	Node(Hexagon* hex, Node* parent, double H): hex(hex), parent(parent), G(0), F(0), H(H){
		if(parent) setParent(parent);
	}
    
	void setParent(Node* parent){
		this->parent = parent;
		G = parent->G + 1;
        
		F = G + H;
        
        /*CCLabelTTF* label =cocos2d::CCLabelTTF::create(StringExtension::toString(H).c_str(), "Arial", 54);
        label->setPosition(ccp(128, 128));
        hex->addChild(label);*/
	}
    
	Hexagon* hex;
	Node* parent; // предведущая ячейка
    
	int G; // суммарная стоимость того чтобы до сюда дойти
	double F;
    double H; // росстояние до конца
};


