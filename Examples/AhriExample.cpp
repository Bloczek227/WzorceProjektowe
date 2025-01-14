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
    f->use_skill(off->r);
    f->use_skill(off->e);
    f->use_skill(off->q);
    f->use_skill(off->w);
    f->use_skill(off->basicAttack);
    f->use_skill(off->r);
    f->use_skill(off->basicAttack);
    f->use_skill(off->r);
    f->use_skill(off->basicAttack);
    f->wait_ticks(30);
    std::cout<<f->total_damage()<<std::endl;
    return 0;
}
