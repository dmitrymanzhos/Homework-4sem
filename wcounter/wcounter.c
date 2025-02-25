#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include "dictionary.h"
#include "parser.h"


int main(int argc, char * argv[]) {
    struct all_words *dict = dictionary_create();
    if (argc < 2) {
        struct parser *p = parser_create();
        parser_open_file(p, NULL);

        char *tmp = parser_get_word(p);
        while (tmp) {
            dictionary_append(dict, tmp);
            free(tmp); 
            tmp = parser_get_word(p);
        }

        parser_destroy(p);
    }

    for (int i = 1; i < argc; i++) { // Начинаем с argv[1]
        struct parser *p = parser_create();
        if (parser_open_file(p, argv[i]) < 0) {
            fprintf(stderr, "Failed to open file: %s\n", argv[i]);
            parser_destroy(p);
            continue;
        }

        char *tmp = parser_get_word(p);
        while (tmp) {
            dictionary_append(dict, tmp);
            free(tmp); 
            tmp = parser_get_word(p);
        }

        parser_destroy(p);
    }

    dict = dictionary_sort(dict);
    dictionary_print(dict);
    dictionary_destroy(dict);

    return 0;
}