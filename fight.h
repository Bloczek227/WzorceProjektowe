#ifndef WP_PROJ_FIGHT_H
#define WP_PROJ_FIGHT_H

#include "champion.h"
#include "skill.h"

class Fight{
public:
    Champion* offensive_champion;
    Champion* defensive_champion;
    Fight(Champion* _offensive_champion,Champion* _defensive_champion):offensive_champion(_offensive_champion),defensive_champion(_defensive_champion){};
    void use_skill(ChampionSkill* skill){
        skill->use_skill(offensive_champion,defensive_champion);
    }
    void tick(){
        defensive_champion->dotHandler->handle();
    }
    void wait_ticks(int ticks){
        for(int i=0;i<ticks;i++)
            tick();
    }
    double total_damage(){ return defensive_champion->maxHP()-defensive_champion->currHP();}
};

#endif //WP_PROJ_FIGHT_H
