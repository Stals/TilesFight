//http://www.policyalmanac.org/games/aStarTutorial_rus.htm
// TODO нужна возможность идти назад (для меня вроде нет, тк без стен нет такого варианта)

#include "AStar.h"
#include "Game.h"

AStar::AStar(){
}

AStar::~AStar(){
	while(!open.empty()){
		delete open.back();
		open.pop_back();
	}
    
	while(!closed.empty()){
		delete closed.back();
		closed.pop_back();
	}
}

std::list<Hexagon*> AStar::findPath(Hexagon* startHex, Hexagon* endHex){
	Node* startingNode = new Node(startHex, NULL);
	open.push_back(startingNode);
    
    
	// Note: выйдет если нет возможного пути, либо через return внутри цикла если путь найден
	while(!open.empty()){
		Node* bestNodeFromOpen = getBestNodeFromOpen();
		//4) Удаляем ее из открытого списка и добавляем в закрытый список.
		removeFromOpen(bestNodeFromOpen);
		closed.push_back(bestNodeFromOpen);
        
		//5) Проверяем все соседние клетки. Игнорируем те, которые находятся в закрытом списке или непроходимы (поверхность со стенами, водой), остальные добавляем в открытый список, если они там еще не находятся. Делаем выбранную клетку "родительской" для всех этих клеток.
        
        
        
		for(int side = 0; side < HexSidesCount; ++side){
            Hexagon* hexAround = Game::current().getBoard()->sideHexAt((HexSide)side, bestNodeFromOpen->hex);
            
			if( !hexAround) continue;
			if( isInClosed(hexAround) ) continue;
			Node* linkInOpen = isInOpen(hexAround);
            
			if( !linkInOpen ){
                
				Node* newNode = new Node(hexAround, bestNodeFromOpen);
				open.push_back(newNode);
				if(hexAround == endHex){
					return getPath(newNode);
				}
                
			}else{
				// Нужно проверить а те которые в open - если считать что мы будем идти из этой точки а не из точки ее parent'a будет дешевле?
				// если да - то подменяем того parent на bestNodeFromOpen
                
				// если дойти из это точки дешевле чем из текущего parent'a того нода - то подменяем parent'a
				if((bestNodeFromOpen->G ) < linkInOpen->parent->G){
					linkInOpen->setParent(bestNodeFromOpen);
				}
			}
		}
	}
	// если не вышли внутри цикла - значит путь небыл найден
	return std::list<Hexagon*>();
}


Node* AStar::getBestNodeFromOpen()
{
	if(open.empty()) return NULL;
	
	std::list<Node*>::iterator bestIt = open.begin();
	for(std::list<Node*>::iterator it = (++open.begin()); it != open.end(); ++it){
		
		if((*it)->F < (*bestIt)->F){
			bestIt = it;
		}
	}
    
	return (*bestIt);
}

void AStar::removeFromOpen(Node* node)
{
	open.remove(node);
}


Node* AStar::isInOpen(Hexagon* hex)
{
    
	for(std::list<Node*>::iterator it = open.begin(); it != open.end(); ++it){
		if((*it)->hex == hex)
            return (*it);
	}
    
	return NULL;
}


bool AStar::isInClosed(Hexagon* hex)
{
	for(std::list<Node*>::iterator it = closed.begin(); it != closed.end(); ++it){
		if((*it)->hex == hex) return true;
	}
    
	return false;
}


std::list<Hexagon*> AStar::getPath(Node* finalNode)
{
	std::list<Hexagon*> result;
    
	Node* node = finalNode;
	while(node != NULL){
		result.push_back(node->hex);
		node = node->parent;
	}
    
	std::reverse(result.begin(), result.end());
	return result;
}


double AStar::hex_distance(Hexagon* hex1, Hexagon* hex2)
{
	return hex_distance(hex1->getXCoord(), hex1->getYCoord(), hex2->getXCoord(), hex2->getYCoord());
}


double AStar::hex_distance(int q1, int r1, int q2, int r2)
{
    return (abs(q1 - q2) + abs(r1 - r2)
            + abs(q1 + r1 - q2 - r2)) / 2;
}
