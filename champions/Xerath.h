#ifndef WP_PROJ_XERATH_H
#define WP_PROJ_XERATH_H

#include <vector>
#include "../champion.h"
#include "../skill.h"

class Xerath:public Champion{
public:
    double baseADLv1() override{return 55;}
    double ADPerLevel() override{return 3;}
    double baseHPLv1() override{return 596;}
    double HPPerLevel() override{return 106;}
    double baseArmorLv1() override{return 22;}
    double ArmorPerLevel() override{return 4.7;}
    double baseMRLv1() override{return 30;}
    double MRPerLevel() override{return 1.3;}


    class BasicAttack:public ChampionSkill{
        Xerath* xerath;
    public:
        BasicAttack(Xerath* xerath_){
            xerath=xerath_;
        }
        bool spell() override{return false;}
        double physical_damage(ChampionInterface* enemyChampion) override{
            return xerath->ad()*(1+xerath->criticalDamage()*xerath->criticalChance()/10000);
        }
    };

    enum WstratEnum{
        center,
        edge
    };
    class Wstrategy:public ChampionSkill{
    public:
        Xerath* xerath;
        Wstrategy(Xerath* xerath_):xerath(xerath_){};
    };
    class Center:public Wstrategy{
    public:
        using Wstrategy::Wstrategy;
        double magic_damage(ChampionInterface* enemyChampion) override{
            return (25+35*xerath->W_level()+0.6*xerath->ap())*1.667;
        }
    };
    class Edge:public Wstrategy{
    public:
        using Wstrategy::Wstrategy;
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 25+35*xerath->W_level()+0.6*xerath->ap();
        }
    };
    class W;
    class W_config{
        Xerath* xerath;
    public:
        W* skill;
        W_config(W* skill_,Xerath* xerath_) {
            xerath=xerath_;
            skill=skill_;
        }
        void choose_strat(WstratEnum strat){
            if(strat==center){
                skill->w_strat=new Center(xerath);
            }
            else if(strat==edge){
                skill->w_strat=new Edge(xerath);
            }
        }
    };

    class Q:public ChampionSkill{
        Xerath* xerath;
    public:
        Q(Xerath* xerath_){
            xerath=xerath_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 30+40*xerath->Q_level()+0.85*xerath->ap();
        }
    };

    class W:public ChampionSkill{
        Xerath* xerath;
    public:
        Wstrategy* w_strat;
        W_config* conf;
        W(Xerath* xerath_){
            xerath=xerath_;
            conf=new W_config(this,xerath);
            conf->choose_strat(center);
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return w_strat->magic_damage(enemyChampion);
        }
    };

    class E:public ChampionSkill{
        Xerath* xerath;
    public:
        E(Xerath* xerath_){
            xerath=xerath_;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 50+30*xerath->E_level()+0.45*xerath->ap();
        }
    };


    class R:public ChampionSkill{
        Xerath* xerath;
        int stacks;
    public:
        R(Xerath* xerath_){
            xerath=xerath_;
            stacks=0;
        }
        double magic_damage(ChampionInterface* enemyChampion) override{
            return 130+50*xerath->R_level()+0.4*xerath->ap()+(15+5*xerath->R_level()+0.05*xerath->ap())*stacks;
        }
        void after_use(Skill* skill, ChampionInterface* enemyChampion) override{
            stacks++;
        }
    };

    BasicAttack* basicAttack;
    Q* q;
    W* w;
    E* e;
    R* r;
    Xerath(int lv_, std::vector<int> skill_levels, std::vector<Item*> items):Champion(lv_,skill_levels,items){
        addBaseStats(this);
        basicAttack=new BasicAttack(this);
        q=new Q(this);
        w=new W(this);
        e=new E(this);
        r=new R(this);
    }
};

#endif //WP_PROJ_XERATH_H
