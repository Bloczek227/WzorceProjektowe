#ifndef WP_PROJ_COSMICDRIVE_H
#define WP_PROJ_COSMICDRIVE_H

#include "../item.h"

class CosmicDrive:public Item{
public:
    int cost() override{return 3000;}
    double flatAP() override{
        return 70;
    }
    double maxHP() override{
        return 350;
    }
};

#endif //WP_PROJ_COSMICDRIVE_H
