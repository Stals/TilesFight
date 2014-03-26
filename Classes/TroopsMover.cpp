//
//  TroopsMover.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/8/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "TroopsMover.h"
#include "CCShake.h"
#include "Hexagon.h"
#include "Game.h"
#include "Army.h"
#include "EffectPlayer.h"

void TroopsMover::moveTroops(std::vector<Hexagon*> &selectedHexagons, Hexagon* endHex)
{
    endHex->setSelected(false);
    for(size_t hexID = 0; hexID < selectedHexagons.size(); ++hexID){
        Hexagon* startHex = selectedHexagons[hexID];
        if(startHex->getTroopsCount() <= 1) continue;
        moveTroops(startHex, endHex);
    }
}

void TroopsMover::moveTroops(Hexagon* startHex, Hexagon* endHex)
{
    //if(!hexArray2D.areConnected(startHex, endHex)) return;
    
    if(startHex != endHex){
        const int troops = startHex->getTroopsCount() - 1;
        startHex->removeTroops(troops);
        
        if(endHex->getOwner() == startHex->getOwner()){
            endHex->addTroops(troops);
        }else{
            if(troops == endHex->getTroopsCount()){
                endHex->removeTroops(troops);
                endHex->changeOwner(0); // TODO NoPlayer вместо 0?
            }else if(troops < endHex->getTroopsCount()){
                endHex->removeTroops(troops);
            }else{ // troops > endHex->getTroopsCount()
                const int firstPlayerTroopsLeft = troops - endHex->getTroopsCount();
                endHex->removeTroops(endHex->getTroopsCount());
                endHex->addTroops(firstPlayerTroopsLeft);
                endHex->changeOwner(startHex->getOwner());
            }
            //shakeAround(endHex, 2);
        }
        if(endHex->getTroopsCount() > 0){
            endHex->runScaleAction();
        }
    }
}

void TroopsMover::moveTroops(std::vector<Army*> armies, Hexagon* endHex)
{
    endHex->setSelected(false);
    for(size_t armyID = 0; armyID < armies.size(); ++armyID){

        moveTroops(armies[armyID], endHex);
    }
    
}

void TroopsMover::moveTroops(Army* army, Hexagon* endHex)
{
    Hexagon* startHex = army->getCurrentHex();
    //if(!hexArray2D.areConnected(startHex, endHex)) return;
    
    const int troops = army->getTroopsCount();
    startHex->removeArmy(army);
    
    if(troops == 0){
        delete army;
        return;
    }
    
    if(endHex->getOwner() == startHex->getOwner()){
        endHex->addArmy(army);
    }else{
        //if(endHex->getOwner()){
        //    EffectPlayer::playAttackEffect();
        //}
        
        // ничья
        if(troops == endHex->getTroopsCount()){
            endHex->removeTroops(troops);
            //endHex->changeOwner(0); // TODO NoPlayer вместо 0?
            delete army;
            
        // выиграл защищающийся
        }else if(troops < endHex->getTroopsCount()){
            endHex->removeTroops(troops);
            delete army;
            
        // выиграл нападающий
        }else{ // troops > endHex->getTroopsCount()
            if(endHex->getOwner()) EffectPlayer::playAttackEffect();
            endHex->changeOwner(startHex->getOwner());
            
            army->removeTroops(endHex->getTroopsCount());
            endHex->removeTroops(endHex->getTroopsCount());
            
            if(army->getTroopsCount() > 0){
                endHex->addArmy(army);
            }else{
                delete army;
            }
        }
        //shakeAround(endHex, 2);
    }
    if((endHex->getTroopsCount() > 0) && (startHex != endHex)){
        endHex->runScaleAction();
    }

}



void TroopsMover::shakeAround(const Hexagon *hex, int strength)
{
    
    //const float dt = 0.5f;
    
    // Shake around
    /*for(int side = 0; side < HexSidesCount; ++side)
     {
     Hexagon* h = sideHexAt((HexSide)side, hex->getXCoord(), hex->getYCoord());
     if(h){
     h->runAction(CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt));
     }
     }*/
    
    // shake all
    //runAction(CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt));
}