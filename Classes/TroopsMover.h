#pragma once

#include <vector>

class Hexagon;
class Army;
class Player;

class TroopsMover{
public:
    
	static void moveTroops(std::vector<Hexagon*> &selectedHexagons, Hexagon* endHex);
    static void moveTroops(Hexagon* startHex, Hexagon* endHex);
    
    static void moveTroops(std::vector<Army*> armies, Hexagon* endHex);
    static void moveTroops(Army* army, Hexagon* endHex);

private:
    enum AttackResult{
        Draw,
        DefenderWins,
        AttackerWins
    };
    
    static void shakeAround(const Hexagon* hex, int strength);
    static void checkAndShake(int armySize1, int armySize2, const Hexagon* hex);
    
    static AttackResult getAttackResult(Army* army, Hexagon* endHex);
    static void handleAttackResult(AttackResult result, Army* army, Hexagon* startHex, Hexagon* endHex);
    
    static void updateAchievements(Player* attacker, AttackResult attackResult, int armySize, int endHexArmySize, const Hexagon* endHex);
};
