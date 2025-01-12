#ifndef WP_PROJ_VERDANTBARRIER_H
#define WP_PROJ_VERDANTBARRIER_H

#include "../item.h"

class VerdantBarrier: public Item{
public:
    int cost() override{return 1600;}
    double flatAP() override{
        return 40;
    }
    double magicResist() override{
        return 25;
    }
};

#endif //WP_PROJ_VERDANTBARRIER_H
