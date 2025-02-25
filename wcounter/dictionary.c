#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct all_words{
    int count;
    char * word;
    struct all_words * next;
};

struct all_words * dictionary_create(){ // конструктор
    struct all_words * all_words = malloc(sizeof(struct all_words));
    *all_words = (struct all_words){0, NULL, NULL};
    return all_words;
}

int dictionary_destroy(struct all_words * all_words){ // деструктор
    struct all_words *p = all_words;
    while(p->next != NULL){
        free(p->word); // ???
        struct all_words * next= p->next;
        free(p);
        p = next;
    };
    return 0;
}

struct all_words * dictionary_append(struct all_words * all_words, char * word){ // добавить слово
    struct all_words *p = all_words;
    while(p->next != NULL){
        if(strcmp(p->word, word) == 0){ //если 
            p->count++;
            return p;
        }
        p = p->next;
    };
    struct all_words * new = malloc(sizeof(struct all_words));
    p->next = new;
    char * word_copy = malloc(sizeof(char *));
    strcpy(word_copy, word);
    *new = (struct all_words){1, word_copy, NULL}; // ???word

    return all_words;
}


struct all_words * dictionary_sort(struct all_words * all_words){ // сортировка ??? проверить
    if (all_words == NULL || all_words->next == NULL) {
        return all_words;
    }

    struct all_words *sorted = NULL;
    struct all_words *current = all_words;

    while (current != NULL) {
        struct all_words *next = current->next;

        if (sorted == NULL || current->count > sorted->count) {
            current->next = sorted;
            sorted = current;
        } else {
            struct all_words *temp = sorted;
            while (temp->next != NULL && temp->next->count >= current->count) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    return sorted;
}


struct all_words * dictionary_print(struct all_words * all_words){ // печать
	struct all_words* tmp;
	printf("List:\n");
	for ( tmp = all_words; tmp != NULL; tmp = tmp->next ) {
		printf("%d\t%s\n", tmp->count, tmp->word);
	}
    return all_words;
}

