#include "dog.h"
#include "cat.h"
#include "animal.h"


int main(){
    struct animal * p1 = cat_create("1");
    struct animal * p2 = dog_create("2");
    struct animal * p = (1>0)?p1:p2;
    p->m->voice(p);
    return 0;
}