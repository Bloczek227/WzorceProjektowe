#ifndef WP_PROJ_VOIDSTAFF_H
#define WP_PROJ_VOIDSTAFF_H


#include "../item.h"

class VoidStaff:public Item{
public:
    int cost() override{return 3000;}
    double flatAP() override{
        return 95;
    }
    double percentageMagicPenetration() override{
        return 40;
    }
};

#endif //WP_PROJ_VOIDSTAFF_H
