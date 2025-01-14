#ifndef WP_PROJ_RUBYCRYSTAL_H
#define WP_PROJ_RUBYCRYSTAL_H

#include "../item.h"

class RubyCrystal:public Item{
public:
    int cost() override{return 400;}
    double maxHP() override{
        return 150;
    }
};

#endif //WP_PROJ_RUBYCRYSTAL_H
