#ifndef WP_PROJ_DOTHANDLER_H
#define WP_PROJ_DOTHANDLER_H

#include "interfaces.h"
#include "skill.h"
#include <unordered_map>
#include <string>

class DotHandler{
public:
    ChampionInterface* champion;
    std::unordered_map<std::string, DOTItemSkill*> dot_item_skills;
    std::unordered_map<std::string, DOTChampionSkill*> dot_champion_skills;
    void add_effect(DOTItemSkill* skill){
        if(dot_item_skills.find(skill->effect_name) != dot_item_skills.end()){
            dot_item_skills[skill->effect_name]->ticksLeft=skill->maxTicks;
        }
        else{
            dot_item_skills.insert({skill->effect_name, skill});
        }
    }
    void add_effect(DOTChampionSkill* skill){
        if(dot_champion_skills.find(skill->effect_name) != dot_champion_skills.end()){
            dot_champion_skills[skill->effect_name]->ticksLeft=skill->maxTicks;
        }
        else{
            dot_champion_skills.insert({skill->effect_name, skill});
        }
    }
    void handle(){
        std::unordered_set<std::string> to_delete;
        for(auto& [k,v]:dot_champion_skills){
            v->use_skill(v->champion,champion);
            v->ticksLeft--;
            if(v->ticksLeft<=0) {
                to_delete.insert(k);
            }
        }
        for(auto& k:to_delete){
            dot_champion_skills.erase(k);
        }
        to_delete=std::unordered_set<std::string>();
        for(auto& [k,v]:dot_item_skills){
            champion->receiveDamage(v,v->champion);
            v->effect(champion);
            v->ticksLeft--;
            if(v->ticksLeft<=0)
                to_delete.insert(k);
        }
        for(auto& k:to_delete){
            dot_item_skills.erase(k);
        }
    }
    DotHandler(ChampionInterface* champion_): champion(champion_){};
};


#endif //WP_PROJ_DOTHANDLER_H
