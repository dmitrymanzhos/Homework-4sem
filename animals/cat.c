#include <stdio.h>
#include <stdlib.h>
#include "cat.h"


struct cat {
    struct animal a;  // наследование от класса animal
};


struct animal* cat_create(char * name){
    struct cat * p = malloc(sizeof(struct cat *));
    p->a.name = name;
    p->a.m->voice = cat_voice; // ???
    return (struct animal *)p;
};


int cat_voice(struct cat* c){
    struct animal * a = (struct animal *)c;
    const char* name = animal_getname(a);
    printf("Cat %s meow!\n", name);
}


// struct animal_m{ // таблица методов
//     void (* voice)(struct animal *);
// };