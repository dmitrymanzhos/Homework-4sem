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


int main(int argc, char * argv[]){
    struct all_words * dict = dictionary_create();

    for(int i = 0; i < argc - 1; i++){
        struct parser * p = parser_create();
        parser_open_file(p, argv[i]);
        char * tmp = parser_get_word(p);
        while(tmp != NULL){
            dictionary_append(dict, tmp);
            tmp = parser_get_word(p);
        }
        parser_destroy(p);
    }

    dictionary_sort(dict);
    dictionary_print(dict);
    return 0;
}
