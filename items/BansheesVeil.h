#ifndef WP_PROJ_BANSHEESVEIL_H
#define WP_PROJ_BANSHEESVEIL_H

#include "../item.h"

class BansheesVeil: public Item{
public:
    int cost() override{return 3000;}
    double flatAP() override{
        return 105;
    }
    double magicResist() override{
        return 40;
    }
};

#endif //WP_PROJ_BANSHEESVEIL_H
