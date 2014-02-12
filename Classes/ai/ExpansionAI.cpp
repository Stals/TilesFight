#include "ExpansionAI.h"
#include "../Player.h"
#include "../Game.h"
#include "../utils/RandomGenerator.h"
#include "../Hexagon.h"
#include "../Army.h"


ExpansionAI::ExpansionAI(Player* player):AbstractAI(player), currentTarget(NULL)
{
    setupCenter();
}


void ExpansionAI::doTurn(float dt)
{
	if(player->getControlledHexagons().size() == 0) return;
    if(!center) setupCenter();

    // if have current target but not currently occupied
    if(currentTarget && (currentTarget->getOwner() != player)){
        // send all armies there
        sendArmies(currentTarget);
        
    }else{
        currentTarget = getClosestUnoccupiedHexagon();
        if(currentTarget){
            CCLog("New Target - x:%lu y:%lu", currentTarget->getXCoord(), currentTarget->getYCoord());
            
        }else{
            CCLog("No targets found");
        }
    }
}

void ExpansionAI::setupCenter()
{
    center = *player->getControlledHexagons().begin();
}

Hexagon* ExpansionAI::getClosestUnoccupiedHexagon()
{
    std::set<Hexagon*> hexagons;
    hexagons.insert(center);
    
    while(true){
        hexagons = getHexagonsAround(hexagons);
        for(std::set<Hexagon*>::const_iterator it = hexagons.begin(); it != hexagons.end(); ++it){
            if((*it)->getOwner() != player){
                return *it;
            }
        }

    }
    // TODO нужно как-то выходить если захвачено все
}

void ExpansionAI::sendArmies(Hexagon* target)
{
    std::set<Hexagon*> controlled = player->getControlledHexagons();
    std::vector<Army*> armies;
    
    // create armies
    for(std::set<Hexagon*>::iterator it = controlled.begin(); it != controlled.end(); ++it){
        armies.push_back((*it)->createArmy(target));
    }
    
    // move armies
    for(size_t i = 0; i < armies.size(); ++i){
        armies[i]->move(0);
    }
}

std::set<Hexagon*> ExpansionAI::getHexagonsAround(const std::set<Hexagon*> &hexagons)
{
    
    // TODO -- тут есть баг в том что вокруг на самом деле неправильно определяется
    // так как в прошлом небыло тех что еще более внутри around их добавляет как новые
    Board* board = Game::current().getBoard();
    
    std::set<Hexagon*> hexagonsAround;

    for(std::set<Hexagon*>::const_iterator it = hexagons.begin(); it != hexagons.end(); ++it){
        Hexagon* hex = *it;
        
        for(int side = 0; side < HexSidesCount; ++side){
            Hexagon* hexAround = board->sideHexAt((HexSide)side, hex);
            if(!hexAround) continue;
            
            if((hexagonsAround.find(hexAround) == hexagonsAround.end()) &&
               (hexagons.find(hexAround) == hexagons.end())){
            
                hexagonsAround.insert(hexAround);
            }
        }
    }
    
    
    return hexagonsAround;
}

