#ifndef WP_PROJ_ITEM_H
#define WP_PROJ_ITEM_H

#include <unordered_set>
#include "interfaces.h"
#include "skill.h"

class Item{
public:
    ChampionInterface* champion;
    virtual int cost()=0;
    virtual double ad(){return 0;}
    virtual double criticalChance(){return 0;}
    virtual double criticalDamage(){return 0;}
    virtual double lethality(){return 0;}
    virtual double percentageArmorPenetration(){return 0;}
    virtual double flatAP(){return 0;}
    virtual double apMultiplier(){return 0;}
    virtual double flatMagicPenetration(){return 0;}
    virtual double percentageMagicPenetration(){return 0;}
    virtual double maxHP(){return 0;}
    virtual double armor(){return 0;}
    virtual double magicResist(){return 0;}
    template<ChampionConcept Champion>
    void setStats(Champion* champ){
        champ->ad_+=ad();
        champ->criticalChance_+=criticalChance();
        champ->criticalDamage_+=criticalDamage();
        champ->lethality_+=lethality();
        champ->percentageArmorPenetration_=1-(1-champ->percentageArmorPenetration())*(1-percentageArmorPenetration());
        champ->flatAP_+= flatAP();
        champ->apMultiplier_+=apMultiplier();
        champ->flatMagicPenetration_+=flatMagicPenetration();
        champ->percentageMagicPenetration_=100-(100-champ->percentageMagicPenetration())*(100-percentageMagicPenetration())/100;
        champ->maxHP_+=maxHP();
        champ->armor_+=armor();
        champ->magicResist_+=magicResist();
    }
    virtual void setChampion(ChampionInterface* champion_){
        champion=champion_;
    }
    virtual void add_observers(){}
};

class ItemSkillsObservers:public ItemSkillsObserversInterface{
public:
    std::unordered_set<ItemSkill*> skills;
    void add(ItemSkill* skill){
        skills.insert(skill);
    }
    void before_use(Skill* skill, ChampionInterface* enemyChampion){
        for(auto x:skills)
            x->before_use(skill,enemyChampion);
    }
    void after_use(Skill* skill, ChampionInterface* enemyChampion){
        for(auto x:skills)
            x->after_use(skill,enemyChampion);
    }
};

#endif //WP_PROJ_ITEM_H
