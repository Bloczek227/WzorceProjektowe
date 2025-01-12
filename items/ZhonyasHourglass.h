#ifndef WP_PROJ_ZHONYASHOURGLASS_H
#define WP_PROJ_ZHONYASHOURGLASS_H

#include "../item.h"

class ZhonyasHourglass: public Item{
public:
    int cost() override{return 3250;}
    double flatAP() override{
        return 105;
    }
    double armor() override{
        return 50;
    }
};

#endif //WP_PROJ_ZHONYASHOURGLASS_H
