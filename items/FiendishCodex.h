#ifndef WP_PROJ_FIENDISHCODEX_H
#define WP_PROJ_FIENDISHCODEX_H

#include "../item.h"

class FiendishCodex: public Item{
public:
    int cost() override{return 850;}
    double flatAP() override{
        return 25;
    }
};

#endif //WP_PROJ_FIENDISHCODEX_H
