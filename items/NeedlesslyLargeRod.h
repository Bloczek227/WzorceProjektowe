#ifndef WP_PROJ_NEEDLESSLYLARGEROD_H
#define WP_PROJ_NEEDLESSLYLARGEROD_H

#include "../item.h"

class NeedlesslyLargeRod:public Item{
public:
    int cost() override{return 1200;}
    double flatAP() override{
        return 65;
    }
};

#endif //WP_PROJ_NEEDLESSLYLARGEROD_H
