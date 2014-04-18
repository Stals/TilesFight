#include "AchievementCounter.h"
#include "AchievementChecker.h"

#define COUNTERS_XML "counters.xml"

CounterContainer::CounterContainer(): autosaveEnabled(true)
{
    counters = new SettingsXML(COUNTERS_XML);
}

CounterContainer* CounterContainer::current()
{
    static CounterContainer container;
    return &container;
}

void CounterContainer::incrementCounter(const std::string& name, int amount)
{
    const int prevAmount = getCounterAmount(name);
    setValue(name, prevAmount + amount);
}

void CounterContainer::setIfBigger(const std::string& name, int amount)
{
    const int prevAmount = getCounterAmount(name);

    if(prevAmount > amount){
        setValue(name, amount);
    }
}

void CounterContainer::setValue(const std::string& counterName, int amount)
{
    counters->setValue(counterName, amount);
    
    if(autosaveEnabled){
        counters->save();
    }
    
    AchievementChecker::current()->checkCounterAcievements(counterName, amount);
}


int CounterContainer::getCounterAmount(const std::string& name)
{
    return counters->getInt(name, 0);
}

void CounterContainer::setAutoSaveEnabled(bool enabled)
{
    this->autosaveEnabled = enabled;
    if(enabled){
        counters->save();
    }
}
