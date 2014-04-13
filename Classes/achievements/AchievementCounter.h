#pragma once

#include <string>

#include "../../lib/data/SettingsXML.h"


class CounterContainer{
public:
    static CounterContainer* current();
    
    void incrementCounter(const std::string& name, int amount = 1);
    void setIfBigger(const std::string& name, int amount);
    
    int getCounterAmount(const std::string& name);
    
private:
    CounterContainer();
    SettingsXML* counters;
    
    // method with autosave
    void setValue(const std::string& counterName, int amount);
};

