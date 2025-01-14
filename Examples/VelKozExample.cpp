#include <iostream>
#include <vector>
#include "../champions.h"
#include "../items.h"
#include "../fight.h"


int main() {
    auto off=new VelKoz(13,{5,5,1,2},std::vector<Item*>({new LiandrysTorment(),new Shadowflame()}));
    auto def=new Ahri(16,{5,3,5,3},std::vector<Item*>({new CosmicDrive(),new RubyCrystal()}));
    auto f=new Fight(off,def);
    f->use_skill(off->e);
    f->use_skill(off->w);
    f->use_skill(off->q);
    f->use_skill(off->r);
    f->wait_ticks(60);
    std::cout<<f->total_damage()<<std::endl;
    return 0;
}
