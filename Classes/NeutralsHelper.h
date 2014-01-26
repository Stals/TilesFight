#pragma once

#include "Addons/TroopsGenerator.h"
#include "Addons/AmoutIncreaser.h"

// TODO ÔÂÂËÏÂÌÓ‚‡Ú¸ - Ú‡Í. Í‡Í ˝ÚÓÚ ÍÎ‡ÒÒ ÔÓ‰ÓÈ‰ÂÚ Ë ‰Îˇ ‡ÒÔÓÎÓÊÂÌËˇ ‡ÒËÈ Ë„ÓÍÓ‚
// ≈ÒÎË Ì‡ÔÏËÂ ÔÂÂ‰‡‚‡Ú¸ 2 Ë„ÓÍ‡, ÚÓ ÒËÏÏÂÚË˜Ì˚È ·Û‰ÂÚ Ë„ÓÍ 2

class NeutralsHelper{
public:
	// ÌÂ ÒÔ‡‚ÌËÚ Ì‡ Ë„ÓÍ‡ı ËÎË ÏËÏÓ Í‡Ú˚!
    
    // TODO сделать чтобы принимало Addon* а не type - тоесть уже созданные передается?
    // а какже тогда компирование и стафф всмысле как мне для второго типа такойже сделать?
    
	static void addNeutrals(Player* player, GeneratorType type, size_t x, size_t y);
	static void addNeutrals(Player* player, Player* player2, GeneratorType type, size_t x, size_t y);

	static void addNeutrals(Player* player, AIncreaserType type, size_t x, size_t y);
	static void addNeutrals(Player* player, Player* player2, AIncreaserType type, size_t x, size_t y);
    
    //static void addNeutralWithAddon(Player* player, Player* player2, Addon* addon1, Addon* addon2, size_t x, size_t y);


private:
	NeutralsHelper();

	static void getSymmetricCoords(size_t x, size_t y, size_t &sym_x, size_t &sym_y);
	static Hexagon* getSymmetricHexagon(Hexagon* hex);
};
