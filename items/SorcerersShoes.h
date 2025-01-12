#ifndef WP_PROJ_SORCERERSSHOES_H
#define WP_PROJ_SORCERERSSHOES_H

#include "../item.h"

class SorcerersShoes: public Item{
public:
    int cost() override{return 1100;}
    double flatMagicPenetration() override{
        return 12;
    }
};

#endif //WP_PROJ_SORCERERSSHOES_H
