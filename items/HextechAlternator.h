#ifndef WP_PROJ_HEXTECHALTERNATOR_H
#define WP_PROJ_HEXTECHALTERNATOR_H

#include "../item.h"
#include "../config.h"
#include "../skill.h"

class HextechAlternatorSkill: public ItemSkill{
public:
    bool used;
    HextechAlternatorSkill(){
        used=false;
    }
    double magic_damage(ChampionInterface* enemyChampion) override{return 65;}
    void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
        if(!used&&skill->spell()){
            used=true;
            enemyChampion->receiveDamage(this,champion);
        }
    };
};

class HextechAlternator: public Item{
public:
    int cost() override{return 1100;}
    double flatAP() override{
        return 45;
    }
    HextechAlternatorSkill* revved;
    HextechAlternator(){
        revved=new HextechAlternatorSkill();
        revved->champion=champion;
    }
    void setChampion(ChampionInterface* champion_)override{
        champion=champion_;
        revved->champion=champion_;
    }
    void add_observers() override{
        champion->getItemSkillsObservers()->add(revved);
    }
};

#endif //WP_PROJ_HEXTECHALTERNATOR_H
