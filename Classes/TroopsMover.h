#pragma once

#include <vector>

class Hexagon;
class Army;

class TroopsMover{
public:
    
	static void moveTroops(std::vector<Hexagon*> &selectedHexagons, Hexagon* endHex);
    static void moveTroops(Hexagon* startHex, Hexagon* endHex);
    
    static void moveTroops(std::vector<Army*> armies, Hexagon* endHex);
    static void moveTroops(Army* army, Hexagon* endHex);

private:
    static void shakeAround(const Hexagon* hex, int strength);

};
