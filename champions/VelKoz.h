#ifndef WP_PROJ_VELKOZ_H
#define WP_PROJ_VELKOZ_H

#include <vector>
#include "../champion.h"
#include "../skill.h"
#include "../config.h"

class VelKoz:public Champion{
public:
    double baseADLv1() override{return 55;}
    double ADPerLevel() override{return 3.1516;}
    double baseHPLv1() override{return 590;}
    double HPPerLevel() override{return 102;}
    double baseArmorLv1() override{return 22;}
    double ArmorPerLevel() override{return 4.7;}
    double baseMRLv1() override{return 30;}
    double MRPerLevel() override{return 1.3;}

    class BasicAttack:public ChampionSkill{
        VelKoz* velkoz;
    public:
        BasicAttack(VelKoz* velkoz_){
            velkoz=velkoz_;
        }
        double physical_damage(ChampionInterface* enemyChampion) override{
            return velkoz->ad()*(1+velkoz->criticalDamage()*velkoz->criticalChance()/10000);
        }
    };

    class Passive:public ChampionSkill{
        VelKoz* velkoz;
    public:
        bool triggered=false;
        int stacks=0;
        Passive(VelKoz* velkoz_){
            velkoz=velkoz_;
        }
        bool spell() override{return false;}
        double true_damage(ChampionInterface* enemyChampion) override{
            return 35+145.0/17*(velkoz->lv()-1)+0.6*velkoz->ap();
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            stacks=0;
            triggered=true;
        }
    };

    class Q:public ChampionSkill{
        VelKoz* velkoz;
    public:
        Q(VelKoz* velkoz_){
            velkoz=velkoz_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 40+40*velkoz->Q_level()+0.9*velkoz->ap();
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            velkoz->passive->stacks++;
            if(velkoz->passive->stacks==3)
                velkoz->passive->use_skill(velkoz,enemyChampion);
        }
    };


    enum WstratEnum{
        onlyW1,
        onlyW2,
        W1_and_W2
    };
    class Wstrategy:public ChampionSkill{
    public:
        VelKoz* velkoz;
        Wstrategy(VelKoz* velkoz_):velkoz(velkoz_){};
    };
    class W1:public Wstrategy{
    public:
        using Wstrategy::Wstrategy;
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 10+20*velkoz->W_level()+0.2*velkoz->ap();
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            velkoz->passive->stacks++;
            if(velkoz->passive->stacks==3)
                velkoz->passive->use_skill(velkoz,enemyChampion);
        }
    };
    class W2:public Wstrategy{
    public:
        using Wstrategy::Wstrategy;
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 15+30*velkoz->W_level()+0.25*velkoz->ap();
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            velkoz->passive->stacks++;
            if(velkoz->passive->stacks==3)
                velkoz->passive->use_skill(velkoz,enemyChampion);
        }
    };
    class W1W2:public Wstrategy{
        W1* w1;
        W2* w2;
    public:
        W1W2(VelKoz* velkoz_): Wstrategy(velkoz_){
            w1=new W1(velkoz_);
            w2=new W2(velkoz_);
        }

        double magic_damage(ChampionInterface* enemyChampion) override{
            return w1->magic_damage(enemyChampion)+w2->magic_damage(enemyChampion);
        }

        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            w1->after_use(skill,enemyChampion);
            w2->after_use(skill,enemyChampion);
        }
    };
    class W;
    class W_config{
        VelKoz* velkoz;
    public:
        W* skill;
        W_config(W* skill_,VelKoz* velkoz_) {
            velkoz=velkoz_;
            skill=skill_;
        }
        void choose_strat(WstratEnum strat){
            if(strat==onlyW1){
                skill->w_strat=new W1(velkoz);
            }
            else if(strat==onlyW2){
                skill->w_strat=new W2(velkoz);
            }
            else if(strat==W1_and_W2){
                skill->w_strat=new W1W2(velkoz);
            }
        }
    };

    class W:public ChampionSkill{
        VelKoz* velkoz;
    public:
        Wstrategy* w_strat;
        W_config* conf;
        W(VelKoz* velkoz_){
            velkoz=velkoz_;
            conf=new W_config(this,velkoz);
            conf->choose_strat(W1_and_W2);
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return w_strat->magic_damage(enemyChampion);
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            w_strat->after_use(skill, enemyChampion);
        }
    };


    class E:public ChampionSkill{
        VelKoz* velkoz;
    public:
        E(VelKoz* velkoz_){
            velkoz=velkoz_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 40+30*velkoz->Q_level()+0.3*velkoz->ap();
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            velkoz->passive->stacks++;
            if(velkoz->passive->stacks==3)
                velkoz->passive->use_skill(velkoz,enemyChampion);
        }
    };



    class RDOT: public DOTChampionSkill{
        VelKoz* velkoz;
        int PassiveTicksLeft;
        int maxPassiveTicks;
    public:
        RDOT(VelKoz* velkoz_){
            effect_name="VelKozR";
            maxTicks=26*Config::Instance()->ticksPerSecond/10;
            maxPassiveTicks=7*Config::Instance()->ticksPerSecond/10;
            ticksLeft=maxTicks;
            PassiveTicksLeft=maxPassiveTicks;
            velkoz=velkoz_;
            champion=velkoz_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{return velkoz->passive->triggered?
                                                                              0:(275+175*velkoz->R_level()+1.25*velkoz->ap())/ 2.6 / Config::Instance()->ticksPerSecond;}
        double true_damage(ChampionInterface* enemyChampion) override{return velkoz->passive->triggered?
                                                                              (275+175*velkoz->R_level()+1.25*velkoz->ap())/ 2.6 / Config::Instance()->ticksPerSecond:0;}
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            PassiveTicksLeft--;
            if(PassiveTicksLeft<=0){
                velkoz->passive->stacks++;
                if(velkoz->passive->stacks==3)
                    velkoz->passive->use_skill(velkoz,enemyChampion);
                PassiveTicksLeft=maxPassiveTicks;
            }
        };

    };
    class R:public ChampionSkill{
        VelKoz* velkoz;
        VelKoz::RDOT* rdot;
    public:
        R(VelKoz* velkoz_){
            velkoz=velkoz_;
            rdot=new VelKoz::RDOT(velkoz_);
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            enemyChampion->getDotHandler()->add_effect(rdot);
        }
    };
    BasicAttack* basicAttack;
    Passive* passive;
    Q* q;
    W* w;
    E* e;
    R* r;
    VelKoz(int lv_, std::vector<int> skill_levels, std::vector<Item*> items):Champion(lv_,skill_levels,items){

        addBaseStats(this);
        basicAttack=new BasicAttack(this);
        passive=new Passive(this);
        q=new Q(this);
        w=new W(this);
        e=new E(this);
        r=new R(this);
    }
};

#endif //WP_PROJ_VELKOZ_H
