#ifndef WP_PROJ_LOSTCHAPTER_H
#define WP_PROJ_LOSTCHAPTER_H

#include "../item.h"

class LostChapter: public Item{
public:
    int cost() override{return 1200;}
    double flatAP() override{
        return 40;
    }
};

#endif //WP_PROJ_LOSTCHAPTER_H
