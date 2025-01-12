#ifndef WP_PROJ_TESTITEM_H
#define WP_PROJ_TESTITEM_H

#include "../item.h"
#include "../skill.h"
#include "../config.h"

class TestItemSkill:public DOTItemSkill{
public:
    TestItemSkill(){
        effect_name="test";
        maxTicks=2*Config::Instance()->ticksPerSecond;
        ticksLeft=maxTicks;
    }
    double magic_damage(ChampionInterface* enemyChampion) override{return 100.0 / Config::Instance()->ticksPerSecond;}
    void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
        enemyChampion->getDotHandler()->add_effect(this);
    };
};
class TestItem:public Item{
public:
    int cost() override{return 0;}
    double flatAP() override{
        return 100;
    }
    TestItemSkill* t;
    TestItem(){

        t=new TestItemSkill();
        t->champion=champion;
    }
    void setChampion(ChampionInterface* champion_)override{
        champion=champion_;
        t->champion=champion_;
    }
    void add_observers() override{
        champion->getItemSkillsObservers()->add(t);
    }
};

#endif //WP_PROJ_TESTITEM_H
