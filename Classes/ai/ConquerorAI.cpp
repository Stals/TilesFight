#include "ConquerorAI.h"
#include "../Player.h"
#include "../Game.h"
#include "../utils/RandomGenerator.h"
#include "../Hexagon.h"
#include "../Army.h"


ConquerorAI::ConquerorAI(Player* player):AbstractAI(player, 5)
{
    
}


void ConquerorAI::doTurn(float dt)
{
    // TODO реже делать ход?
    
    // TODO - двигает рандомную часть войск (сколько нужно решить)
    std::set<Hexagon*> controlledHexagons = player->getControlledHexagons();
	if(controlledHexagons.size() == 0) return;
    
    
    for(std::set<Hexagon*>::iterator hexagonIt = controlledHexagons.begin(); hexagonIt != controlledHexagons.end(); ++hexagonIt){
        
        Hexagon* hex = (*hexagonIt);
        if(hex->getTroopsCount() > 0){
            Hexagon* target = getClosestUnoccupiedAddon(hex);
            if(!target){
                CCLOG("Warning: No targets found - ending turn");
                return;
            }
            
            // TODO нельзя сразу двигать - она может переместиться сразу много раз
                // Это решается задержкой внутри create которая сама подвинет?
            hex->createArmy(target)->move(0);
        }
    }
}



Hexagon* ConquerorAI::getClosestUnoccupiedAddon(Hexagon* hexagon)
{
    std::set<Hexagon*> hexagons;
    hexagons.insert(hexagon);
    
    while(true){
        hexagons = getHexagonsAround(hexagons);
        for(std::set<Hexagon*>::const_iterator it = hexagons.begin(); it != hexagons.end(); ++it){
            
            if((*it)->getOwner() != player){
                if((*it)->hasAddon()){
                    return *it;
                }
            }
        }
    }
    
    return NULL;
}



std::set<Hexagon*> ConquerorAI::getHexagonsAround(const std::set<Hexagon*> &hexagons)
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

