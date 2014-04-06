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

private:
    User();
    
    static User* instance;
    SettingsXML* settings;
    
    // methods with autosave
    void setValue(const std::string& key, bool value);
};