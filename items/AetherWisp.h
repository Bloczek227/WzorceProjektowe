#ifndef WP_PROJ_AETHERWISP_H
#define WP_PROJ_AETHERWISP_H

#include "../item.h"

class AetherWisp:public Item{
public:
    int cost() override{return 900;}
    double flatAP() override{
        return 30;
    }
};

#endif //WP_PROJ_AETHERWISP_H
