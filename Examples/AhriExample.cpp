#include <iostream>
#include <vector>
#include "../champions.h"
#include "../items.h"
#include "../fight.h"







int main() {
    Ahri* off=new Ahri(18,{5,5,5,3},std::vector<Item*>({new RabadonsDeathcap(),new VoidStaff(),new LiandrysTorment()}));
    Ahri* def=new Ahri(17,{5,4,5,3},std::vector<Item*>({new CosmicDrive()}));
    auto f=new Fight(off,def);
    off->q->conf->choose_strat(Ahri::Q1_and_Q2);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->use_skill(off->r);
    f->use_skill(off->e);
    f->use_skill(off->q);
    f->use_skill(off->w);
    f->use_skill(off->basicAttack);
    f->use_skill(off->r);
    f->use_skill(off->basicAttack);
    f->use_skill(off->r);
    f->use_skill(off->basicAttack);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->wait_ticks(20);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    return 0;
}
