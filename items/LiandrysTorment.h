#ifndef WP_PROJ_LIANDRYSTORMENT_H
#define WP_PROJ_LIANDRYSTORMENT_H


#include "../item.h"
#include "../config.h"
#include "../skill.h"
#include "../dotHandler.h"

class LiandrysTormentSkill: public DOTItemSkill{
public:
    LiandrysTormentSkill(){
        effect_name="LiandrysTormentSkill";
        maxTicks=3*Config::Instance()->ticksPerSecond;
        ticksLeft=maxTicks;
    }
    double magic_damage(ChampionInterface* enemyChampion) override{return 0.02 * enemyChampion->maxHP() / Config::Instance()->ticksPerSecond;}
    void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
        enemyChampion->getDotHandler()->add_effect(this);
    };
};

class LiandrysTorment: public Item{
public:
    int cost() override{return 3200;}
    double flatAP() override{
        return 70;
    }
    double maxHP() override{
        return 300;
    }
    LiandrysTormentSkill* torment;
    LiandrysTorment(){

        torment=new LiandrysTormentSkill();
        torment->champion=champion;
    }
    void setChampion(ChampionInterface* champion_)override{
        champion=champion_;
        torment->champion=champion_;
    }
    void add_observers() override{
        champion->getItemSkillsObservers()->add(torment);
    }
};

#endif //WP_PROJ_LIANDRYSTORMENT_H
