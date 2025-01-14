#ifndef WP_PROJ_LIANDRYSTORMENT_H
#define WP_PROJ_LIANDRYSTORMENT_H


#include "../item.h"
#include "../config.h"
#include "../skill.h"
#include "../dotHandler.h"

class LiandrysTormentTorment: public DOTItemSkill{
public:
    LiandrysTormentTorment(){
        effect_name="LiandrysTormentTorment";
        maxTicks=3*Config::Instance()->ticksPerSecond;
        ticksLeft=maxTicks;
    }
    double magic_damage(ChampionInterface* enemyChampion) override{return 0.02 * enemyChampion->maxHP() / Config::Instance()->ticksPerSecond;}
    void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
        if(skill->spell())
            enemyChampion->getDotHandler()->add_effect(this);
    }
};


class LiandrysTormentSuffering: public DOTItemSkill{
public:
    int sufferingTicks;
    int sufferingStacks;
    LiandrysTormentSuffering(){
        effect_name="LiandrysTormentSuffering";
        maxTicks=3*Config::Instance()->ticksPerSecond;
        ticksLeft=maxTicks;
        sufferingTicks=Config::Instance()->ticksPerSecond;;
        sufferingStacks=0;
    }
    void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
        enemyChampion->getDotHandler()->add_effect(this);
    }
    void effect(ChampionInterface* enemyChampion) override{
        sufferingTicks--;
        if(sufferingTicks==0&&sufferingStacks<3){
            champion->setDamageMultiplier(champion->damageMultiplier()/(1+0.02*sufferingStacks)*(1.02+0.02*sufferingStacks));
            sufferingStacks++;
            sufferingTicks=Config::Instance()->ticksPerSecond;
        }
    }
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
    LiandrysTormentTorment* torment;
    LiandrysTormentSuffering* suffering;
    LiandrysTorment(){

        torment=new LiandrysTormentTorment();
        torment->champion=champion;
        suffering=new LiandrysTormentSuffering();
        suffering->champion=champion;
    }
    void setChampion(ChampionInterface* champion_)override{
        champion=champion_;
        torment->champion=champion_;
        suffering->champion=champion_;
    }
    void add_observers() override{
        champion->getItemSkillsSubject()->add(torment);
        champion->getItemSkillsSubject()->add(suffering);
    }
};

#endif //WP_PROJ_LIANDRYSTORMENT_H
