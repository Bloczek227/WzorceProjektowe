#ifndef WP_PROJ_SKILL_H
#define WP_PROJ_SKILL_H

#include "interfaces.h"

class Skill{
public:
    ChampionInterface* champion;
    virtual bool spell(){return true;}
    virtual double physical_damage(ChampionInterface* enemyChampion){
        return 0;
    }
    virtual double magic_damage(ChampionInterface* enemyChampion){
        return 0;
    }
    virtual double true_damage(ChampionInterface* enemyChampion){
        return 0;
    }
    virtual void before_use(Skill* skill, ChampionInterface* enemyChampion){};
    virtual void after_use(Skill* skill, ChampionInterface* enemyChampion){};
};

class ChampionSkill:public Skill{
public:
    void use_skill(ChampionInterface* offensive_champion, ChampionInterface* defensive_champion){
        offensive_champion->getItemSkillsSubject()->before_use(this, defensive_champion);
        before_use(nullptr,defensive_champion);
        defensive_champion->receiveDamage(this,offensive_champion);
        offensive_champion->getItemSkillsSubject()->after_use(this, defensive_champion);
        after_use(nullptr,defensive_champion);
    }
};
class ItemSkill:public Skill{
};

class DOTItemSkill:public ItemSkill{
public:
    int ticksLeft=0;
    int maxTicks=0;
    std::string effect_name;
    virtual double physical_damage(ChampionInterface* enemyChampion){return 0;};
    virtual double magic_damage(ChampionInterface* enemyChampion){return 0;};
    virtual double true_damage(ChampionInterface* enemyChampion){return 0;}
    virtual void effect(ChampionInterface* enemyChampion){};
};

class DOTChampionSkill:public ChampionSkill{
public:
    int ticksLeft=0;
    int maxTicks=0;
    std::string effect_name;
    virtual double physical_damage(ChampionInterface* enemyChampion){return 0;};
    virtual double magic_damage(ChampionInterface* enemyChampion){return 0;};
    virtual double true_damage(ChampionInterface* enemyChampion){return 0;}
};

#endif //WP_PROJ_SKILL_H
