#pragma once

#include <vector>

class Hexagon;

class TroopsMover{
public:
    
	static void moveTroops(std::vector<Hexagon*> &selectedHexagons, Hexagon* endHex);
    static void moveTroops(Hexagon* startHex, Hexagon* endHex);

private:
    static void shakeAround(const Hexagon* hex, int strength);

};
