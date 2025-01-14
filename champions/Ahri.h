#ifndef WP_PROJ_AHRI_H
#define WP_PROJ_AHRI_H

#include <vector>
#include "../champion.h"
#include "../skill.h"

class Ahri:public Champion{
public:
    double baseADLv1() override{return 53;}
    double ADPerLevel() override{return 3;}
    double baseHPLv1() override{return 590;}
    double HPPerLevel() override{return 104;}
    double baseArmorLv1() override{return 21;}
    double ArmorPerLevel() override{return 4.7;}
    double baseMRLv1() override{return 30;}
    double MRPerLevel() override{return 1.3;}


    class BasicAttack:public ChampionSkill{
        Ahri* ahri;
    public:
        BasicAttack(Ahri* ahri_){
            ahri=ahri_;
        }
        bool spell() override{return false;}
        double physical_damage(ChampionInterface* enemyChampion) override{
            return ahri->ad()*(1+ahri->criticalDamage()*ahri->criticalChance()/10000);
        }
    };

    enum QstratEnum{
        onlyQ1,
        onlyQ2,
        Q1_and_Q2
    };
    class Qstrategy:public ChampionSkill{
    public:
        Ahri* ahri;
        Qstrategy(Ahri* ahri_):ahri(ahri_){};
    };
    class Q1:public Qstrategy{
    public:
        using Qstrategy::Qstrategy;
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 15+25*ahri->Q_level()+0.5*ahri->ap();
        }
    };
    class Q2:public Qstrategy{
    public:
        using Qstrategy::Qstrategy;
        double true_damage(ChampionInterface* enemyChampion) override{
            return 15+25*ahri->Q_level()+0.5*ahri->ap();
        }
    };
    class Q1Q2:public Qstrategy{
        Q1* q1;
        Q2* q2;
    public:
        Q1Q2(Ahri* ahri_): Qstrategy(ahri_){
            q1=new Q1(ahri);
            q2=new Q2(ahri);
        }

        double magic_damage(ChampionInterface* enemyChampion) override{
            return q1->magic_damage(enemyChampion);
        }
        double true_damage(ChampionInterface* enemyChampion) override{
            return q2->true_damage(enemyChampion);
        }
    };
    class Q;
    class Q_config{
        Ahri* ahri;
    public:
        Q* skill;
        Q_config(Q* skill_,Ahri* ahri_) {
            ahri=ahri_;
            skill=skill_;
        }
        void choose_strat(QstratEnum strat){
            if(strat==onlyQ1){
                skill->q_strat=new Q1(ahri);
            }
            else if(strat==onlyQ2){
                skill->q_strat=new Q2(ahri);
            }
            else if(strat==Q1_and_Q2){
                skill->q_strat=new Q1Q2(ahri);
            }
        }
    };

    class Q:public ChampionSkill{
        Ahri* ahri;
    public:
        Qstrategy* q_strat;
        Q_config* conf;
        Q(Ahri* ahri_){
            ahri=ahri_;
            conf=new Q_config(this,ahri);
            conf->choose_strat(Q1_and_Q2);
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return q_strat->magic_damage(enemyChampion);
        }
        double true_damage(ChampionInterface* enemyChampion) override{
            return q_strat->true_damage(enemyChampion);
        }
    };



    class W:public ChampionSkill{
        Ahri* ahri;
    public:
        W(Ahri* ahri_){
            ahri=ahri_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 32+40*ahri->W_level()+0.48*ahri->ap();
        }
    };


    class E:public ChampionSkill{
        Ahri* ahri;
    public:
        E(Ahri* ahri_){
            ahri=ahri_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 40+40*ahri->E_level()+0.75*ahri->ap();
        }
    };


    class R:public ChampionSkill{
        Ahri* ahri;
    public:
        R(Ahri* ahri_){
            ahri=ahri_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 30+30*ahri->R_level()+0.35*ahri->ap();
        }
    };

    BasicAttack* basicAttack;
    Q* q;
    W* w;
    E* e;
    R* r;
    Ahri(int lv_, std::vector<int> skill_levels, std::vector<Item*> items):Champion(lv_,skill_levels,items){

        addBaseStats(this);
        basicAttack=new BasicAttack(this);
        q=new Q(this);
        w=new W(this);
        e=new E(this);
        r=new R(this);
    }
};

#endif //WP_PROJ_AHRI_H
