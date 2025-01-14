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
    void setStats(ChampionInterface* champ){
        champ->setAD(champ->ad()+ad());
        champ->setCriticalChance(champ->criticalChance()+criticalChance());
        champ->setCriticalDamage(champ->criticalDamage()+criticalDamage());
        champ->setLethality(champ->lethality()+lethality());
        champ->setPercentageArmorPenetration(100-(100-champ->percentageArmorPenetration())*(100-percentageArmorPenetration()));
        champ->setFlatAP(champ->flatAP()+flatAP());
        champ->setAPMultiplier(champ->apMultiplier()+apMultiplier());
        champ->setFlatMagicPenetration(champ->flatMagicPenetration()+flatMagicPenetration());
        champ->setPercentageMagicPenetration(100-(100-champ->percentageMagicPenetration())*(100-percentageMagicPenetration())/100);
        champ->setMaxHP(champ->maxHP()+maxHP());
        champ->setArmor(champ->armor()+armor());
        champ->setMagicResist(champ->magicResist()+magicResist());
    }
    virtual void setChampion(ChampionInterface* champion_){
        champion=champion_;
    }
    virtual void add_observers(){}
};

class ItemSkillsSubject: public ItemSkillsSubjectInterface{
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
