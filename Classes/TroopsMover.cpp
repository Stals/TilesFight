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
#include "achievements/AchievementCounter.h"
#include "Addons/Addon.h"

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
    // used for achievements and shake
    const int armySize = army->getTroopsCount();
    const int endHexArmySize = endHex->getTroopsCount();
    Hexagon* startHex = army->getCurrentHex();
    
    const int troops = army->getTroopsCount();
    startHex->removeArmy(army);
    
    if(troops == 0){
        delete army;
        return;
    }
    
    if(endHex->getOwner() == startHex->getOwner()){
        endHex->addArmy(army);
    }else{
        
        AttackResult attackResult = getAttackResult(army, endHex);
        updateAchievements(army->getCurrentHex()->getOwner(), attackResult, armySize, endHexArmySize, endHex);
        handleAttackResult(attackResult, army, startHex, endHex);
        
        if(attackResult == DefenderWins){
            if(endHex->getOwner()) EffectPlayer::playAttackEffect();
        }
        
        checkAndShake(armySize, endHexArmySize, endHex);
        
    }
    
    if((endHex->getTroopsCount() > 0) && (startHex != endHex)){
        endHex->runScaleAction();
    }

}

void TroopsMover::checkAndShake(int armySize1, int armySize2, const Hexagon* hex)
{
    if(armySize1 >= 500 && armySize2 >= 250){
        shakeAround(hex, 4);
    }
    else if(armySize1 >= 250 && armySize2 >= 125){
        shakeAround(hex, 3);
    }
    else if(armySize1 >= 100 && armySize2 >= 50){
        shakeAround(hex, 2);
    }
}


void TroopsMover::shakeAround(const Hexagon *hex, int strength)
{
    const float dt = 0.75f;
   
    // Shake around
    for(int side = 0; side < HexSidesCount; ++side){
         Hexagon* h = Game::current().getBoard()->sideHexAt((HexSide)side, hex->getXCoord(), hex->getYCoord());
         if(h){
             h->shake(dt, strength);
         }
     }
    
    // shake all
    //Game::current().getBoard()->runAction(CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt));
}

TroopsMover::AttackResult TroopsMover::getAttackResult(Army* army, Hexagon* endHex)
{
    const int troops = army->getTroopsCount();
    
    if(troops == endHex->getTroopsCount()){
        return Draw;
        
    }else if(troops < endHex->getTroopsCount()){
        return DefenderWins;
        
    }else{ // troops > endHex->getTroopsCount()
        return AttackerWins;
    }
}

void TroopsMover::handleAttackResult(AttackResult result, Army* army, Hexagon* startHex, Hexagon* endHex)
{
    const int troops = army->getTroopsCount();
    //if(!hexArray2D.areConnected(startHex, endHex)) return;
    
    if(result == Draw){
        endHex->removeTroops(troops);
        //endHex->changeOwner(0); // TODO NoPlayer вместо 0?
        delete army;
        
    }else if(result == DefenderWins){
        endHex->removeTroops(troops);
        delete army;
        
    }else if(result == AttackerWins){
        
        endHex->changeOwner(startHex->getOwner());
        
        army->removeTroops(endHex->getTroopsCount());
        endHex->removeTroops(endHex->getTroopsCount());
        
        if(army->getTroopsCount() > 0){
            endHex->addArmy(army);
        }else{
            delete army;
        }
    }
}

void TroopsMover::updateAchievements(Player* attacker, AttackResult attackResult, int armySize, int endHexArmySize, const Hexagon* endHex)
{
    if((armySize >= 500) && (endHexArmySize >= 500)){
        CounterContainer::current()->incrementCounter("500_on_500");
    }
    
    // only for real players
    if(attacker && attacker->isAI()) return;
    
    if(attackResult == AttackerWins){
        CounterContainer::current()->incrementCounter("capture_sector");
   
        if(endHex->getOwner() && (endHex->getOwner()->getAiType() == AbstractAI::NoAI)){
            CounterContainer::current()->incrementCounter("capture_neutral");
        }
        
        if(endHex->hasAddon()){
            if(endHex->getAddon()->getType() == Addon::Generator){
                CounterContainer::current()->incrementCounter("capture_generator");
            }
        }
    }
}