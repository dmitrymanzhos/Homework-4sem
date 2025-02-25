#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct all_words{
    int count;
    char * word;
    struct all_words * next;
};

struct all_words * dictionary_create(){
    struct all_words * all_words = malloc(sizeof(struct all_words));
    if(!all_words) return NULL;
    *all_words = (struct all_words){0, NULL, NULL};
    return all_words;
}

int dictionary_destroy(struct all_words * all_words){
    struct all_words *p = all_words;
    while(p != NULL){
        free(p->word);
        struct all_words * next = p->next;
        free(p);
        p = next;
    }
    return 0;
}

struct all_words * dictionary_append(struct all_words * all_words, char * word) {
    if (!all_words || !word) return all_words;

    struct all_words *p = all_words;
    while (p->next != NULL) {
        if (p->word && strcmp(p->word, word) == 0) {
            p->count++;
            return all_words;
        }
        p = p->next;
    }

    if (p->word && strcmp(p->word, word) == 0) {
        p->count++;
        return all_words;
    }

    struct all_words *new = malloc(sizeof(struct all_words));
    if (!new) {
        perror("malloc");
        return all_words;
    }

    char *word_copy = malloc(strlen(word) + 1);
    if (!word_copy) {
        perror("malloc");
        free(new);
        return all_words;
    }

    strcpy(word_copy, word);
    *new = (struct all_words){1, word_copy, NULL};
    p->next = new;

    return all_words;
}

struct all_words * dictionary_sort(struct all_words * all_words) {
    if (!all_words || !all_words->next) {
        return all_words;
    }

    struct all_words *sorted = NULL;

    while (all_words) {
        struct all_words *current = all_words;
        all_words = all_words->next;

        if (!sorted || current->count > sorted->count) {
            current->next = sorted;
            sorted = current;
        } else {
            struct all_words *temp = sorted;
            while (temp->next && temp->next->count >= current->count) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

struct all_words * dictionary_print(struct all_words * all_words) {
    if (!all_words) {
        printf("Dictionary is empty.\n");
        return NULL;
    }

    printf("List:\n");
    struct all_words *tmp = all_words;
    while (tmp) {
        if (tmp->word) {
            printf("%d\t%s\n", tmp->count, tmp->word);
        }
        tmp = tmp->next;
    }

    return all_words;
}