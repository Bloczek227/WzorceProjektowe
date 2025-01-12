#ifndef WP_PROJ_BLASTINGWAND_H
#define WP_PROJ_BLASTINGWAND_H

#include "../item.h"

class BlastingWand:public Item{
public:
    int cost() override{return 850;}
    double flatAP() override{
        return 45;
    }
};

#endif //WP_PROJ_BLASTINGWAND_H
