#ifndef WP_PROJ_SEEKERSARMGUARD_H
#define WP_PROJ_SEEKERSARMGUARD_H

#include "../item.h"

class SeekersArmguard: public Item{
public:
    int cost() override{return 1600;}
    double flatAP() override{
        return 40;
    }
    double armor() override{
        return 25;
    }
};

#endif //WP_PROJ_SEEKERSARMGUARD_H
