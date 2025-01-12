#include <iostream>
#include <vector>
#include "../champions.h"
#include "../items.h"
#include "../fight.h"







int main() {
    VelKoz* off=new VelKoz(13,{5,5,1,2},std::vector<Item*>({new RabadonsDeathcap(),new LiandrysTorment()}));
    Ahri* def=new Ahri(16,{5,3,5,3},std::vector<Item*>({new CosmicDrive()}));
    auto f=new Fight(off,def);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->use_skill(off->e);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->use_skill(off->w);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->use_skill(off->q);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->use_skill(off->r);
    f->wait_ticks(26);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->wait_ticks(10);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->wait_ticks(10);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->wait_ticks(10);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    f->wait_ticks(10);
    std::cout<<f->defensive_champion->currHP()<<std::endl;
    return 0;
}
