#include <stdio.h>
#include <stdlib.h>
#include "dog.h"


struct dog {
    struct animal a; // наследование от класса animal
};


struct animal* dog_create(char * name){
    struct dog * p = malloc(sizeof(struct dog *));
    p->a.name = name;
    p->a.m->voice = dog_voice; // ???
    return (struct animal *)p;
};


int dog_voice(struct dog* d){
    struct animal * a = (struct animal *)d;
    const char* name = animal_getname(a);
    printf("dog %s gav!\n", name);
}

