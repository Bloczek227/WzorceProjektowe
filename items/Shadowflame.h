#ifndef WP_PROJ_SHADOWFLAME_H
#define WP_PROJ_SHADOWFLAME_H

#include "../item.h"

class ShadowflameSkill: public ItemSkill{
public:
    bool triggered;
    ShadowflameSkill(){
        triggered=false;
    }
    void before_use(Skill* skill, ChampionInterface* enemyChampion) override{
        if((!triggered)&&(enemyChampion->currHP()/enemyChampion->maxHP()<0.4)){
            champion->setMagicDamageMultiplier(champion->magicDamageMultiplier()*1.2);
            champion->setDamageMultiplier(champion->damageMultiplier()*1.2);
            triggered=true;
        }
    }
};

class Shadowflame: public Item{
public:
    int cost() override{return 3200;}
    double flatAP() override{
        return 110;
    }
    double flatMagicPenetration() override{
        return 15;
    }
    ShadowflameSkill* cinderbloom;
    Shadowflame(){
        cinderbloom=new ShadowflameSkill();
        cinderbloom->champion=champion;
    }
    void setChampion(ChampionInterface* champion_)override{
        champion=champion_;
        cinderbloom->champion=champion_;
    }
    void add_observers() override{
        champion->getItemSkillsSubject()->add(cinderbloom);
    }
};

#endif //WP_PROJ_SHADOWFLAME_H
