#pragma once

#include <string>

class SettingsXML;
class User{
public:
    static User* current();
    
    void init();
    
    bool isMusicEnabled();
    void setMusicEnable(bool enabled);
    bool isEffectsEnabled();
    void setEffectsEnable(bool enabled);
    
    // player colors
    int getVSHumanColor1();
    int getVSHumanColor2();
    int getVSAIColor();
    
    void setVSHumanColor1(int index);
    void setVSHumanColor2(int index);
    void setVSAIColor(int index);
    

private:
    User();
    
    static User* instance;
    SettingsXML* settings;
    
    // methods with autosave
    void setValue(const std::string& key, bool value);
    void setValue(const std::string& key, int value);
};