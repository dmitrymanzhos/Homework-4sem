#include "animal.h"

struct animal{
    char * name;
    struct animal_m * m;
};


struct animal_m{ // таблица методов
    void (* voice)(struct animal *);
};


char * animal_getname(struct animal * a){ // ??????
    return a->name;
}
