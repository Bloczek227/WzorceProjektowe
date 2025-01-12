#ifndef WP_PROJ_CRYPTBLOOM_H
#define WP_PROJ_CRYPTBLOOM_H

#include "../item.h"

class Cryptbloom:public Item{
public:
    int cost() override{return 2850;}
    double flatAP() override{
        return 60;
    }
    double percentageMagicPenetration() override{
        return 30;
    }
};

#endif //WP_PROJ_CRYPTBLOOM_H
