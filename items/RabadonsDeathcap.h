#ifndef WP_PROJ_RABADONSDEATHCAP_H
#define WP_PROJ_RABADONSDEATHCAP_H

#include "../item.h"

class RabadonsDeathcap:public Item{
public:
    int cost() override{return 3600;}
    double flatAP() override{
        return 130;
    }
    double apMultiplier() override{
        return 0.3;
    }
};

#endif //WP_PROJ_RABADONSDEATHCAP_H
