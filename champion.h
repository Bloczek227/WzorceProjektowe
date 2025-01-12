#ifndef WP_PROJ_CHAMPION_H
#define WP_PROJ_CHAMPION_H

#include <vector>
#include <unordered_map>
#include "interfaces.h"
#include "skill.h"
#include "item.h"
#include "dotHandler.h"

class ChampionLevel{
public:
    int lv_=1;
    int Q_level_=0;
    int W_level_=0;
    int E_level_=0;
    int R_level_=0;
};

class ChampionPhysicalStats{
public:
    double ad_=0;
    double criticalChance_=0;
    double criticalDamage_=0;
    double lethality_=0;
    double percentageArmorPenetration_=0;
};

class ChampionMagicStats{
public:
    double flatAP_=0;
    double apMultiplier_=1;
    double flatMagicPenetration_=0;
    double percentageMagicPenetration_=0;
};

class ChampionDefensiveStats{
public:
    double maxHP_=0;
    double armor_=0;
    double magicResist_=0;
    double currHP_=0;
};

class Champion: public ChampionLevel, public ChampionPhysicalStats, public ChampionMagicStats,
        public ChampionDefensiveStats, public ChampionInterface{
public:
    int lv() const override{return lv_;};
    int Q_level() const override{return Q_level_;}
    int W_level() const override{return W_level_;}
    int E_level() const override{return E_level_;}
    int R_level() const override{return R_level_;}
    double baseCriticalDamage() override {return 75;}
    double baseAD() override{return baseADLv1()+(0.685+lv()*0.0175)*(lv()-1)*ADPerLevel();}
    double baseHP() override{return baseHPLv1()+(0.685+lv()*0.0175)*(lv()-1)*HPPerLevel();}
    double baseArmor() override{return baseArmorLv1()+(0.685+lv()*0.0175)*(lv()-1)*ArmorPerLevel();}
    double baseMR() override{return baseMRLv1()+(0.685+lv()*0.0175)*(lv()-1)*MRPerLevel();}
    double ad() const override{return ad_;}
    double criticalChance() const override{return criticalChance_;}
    double criticalDamage() const override{return criticalDamage_;}
    double lethality() const override{return lethality_;}
    double percentageArmorPenetration() const override{return percentageArmorPenetration_;}
    double flatAP() const override{return flatAP_;}
    double apMultiplier() const override{return apMultiplier_;}
    double flatMagicPenetration() const override{return flatMagicPenetration_;}
    double percentageMagicPenetration() const override{return percentageMagicPenetration_;}
    double maxHP() const override{return maxHP_;}
    double armor() const override{return armor_;}
    double magicResist() const override{return magicResist_;}
    double currHP() const override{return currHP_;}
    double ap() const override{return flatAP()*apMultiplier();}
    std::vector<Item*> items;
    ItemSkillsObservers* itemSkillsObservers;
    ItemSkillsObservers* getItemSkillsObservers() const override{return itemSkillsObservers;}
    DotHandler* dotHandler;
    DotHandler* getDotHandler() const override{return dotHandler;}
    Champion();
    Champion(int lv__,std::vector<int> skill_levels,const std::vector<Item*>& items_){
        lv_=lv__;
        Q_level_=skill_levels[0];
        W_level_=skill_levels[1];
        E_level_=skill_levels[2];
        R_level_=skill_levels[3];
        items=items_;
        itemSkillsObservers=new ItemSkillsObservers();
        for(auto item:items_) {
            item->setChampion(this);
            item->setStats(this);
            item->add_observers();
        }
        dotHandler=new DotHandler(this);
    }
    void addBaseStats(Champion* derived) override{
        ad_+=derived->baseAD();
        maxHP_+=derived->baseHP();
        armor_+=derived->baseArmor();
        magicResist_+=derived->baseMR();
        criticalDamage_+=derived->baseCriticalDamage();
        currHP_=maxHP();
    };
    void receiveDamage(Skill* skill, ChampionInterface* offensive_champion) override{
        double effective_armor=armor()*(100-offensive_champion->percentageArmorPenetration())/100-offensive_champion->lethality();
        double physical_damage=effective_armor>=0?
                               skill->physical_damage(this)*(100/(100+effective_armor)):
                               skill->physical_damage(this)*(2-(100/(100-effective_armor)));
        double effective_magic_resist=magicResist()*(100-offensive_champion->percentageMagicPenetration())/100-
                                      offensive_champion->flatMagicPenetration();
        double magic_damage=effective_magic_resist>=0?
                            skill->magic_damage(this)*(100/(100+effective_magic_resist)):
                            skill->magic_damage(this);
        currHP_-=physical_damage+magic_damage+skill->true_damage(this);
    }
};

#endif //WP_PROJ_CHAMPION_H
