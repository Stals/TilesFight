#pragma once

#include <string>

class EffectPlayer{
public:
    static void playSelectionEffect();
    static void playAttackEffect();
    static void playShakeEffect();
    
    static void playEffect(const std::string&, bool loop, float pitch, float gain);
private:
    EffectPlayer();
};