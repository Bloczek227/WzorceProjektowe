#ifndef WP_PROJ_AMPLIFYINGTOME_H
#define WP_PROJ_AMPLIFYINGTOME_H

#include "../item.h"

class AmplifyingTome:public Item{
public:
    int cost() override{return 400;}
    double flatAP() override{
        return 20;
    }
};

#endif //WP_PROJ_AMPLIFYINGTOME_H
