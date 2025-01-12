#ifndef WP_PROJ_DORANSRING_H
#define WP_PROJ_DORANSRING_H

#include "../item.h"

class DoransRing:public Item{
public:
    int cost() override{return 400;}
    double flatAP() override{
        return 18;
    }
    double maxHP() override{
        return 80;
    }
};
#endif //WP_PROJ_DORANSRING_H
