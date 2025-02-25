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
#include "parser.h"

struct parser{
    int fp_in;
};

struct parser * parser_create(){ // конструктор
    struct parser * parser = malloc(sizeof(struct parser));
    *parser = (struct parser){-1};
    return parser;
}

int parser_destroy(struct parser * parser){ // деструктор
    free(parser);
    return 0;
}

char * parser_get_word(struct parser * parser){ // считываем одно слово из файла, TODO: сделать через getchar() или что-то такое - лучше
    char buf[32];

    char tmp = read(parser->fp_in, buf, 1);
    while(!isalpha(tmp)){
        if(tmp == EOF) return NULL;
        tmp = read(parser->fp_in, buf, 1);
    }
    int i = 1;
    while(isalpha(read(parser->fp_in, buf+i, 1))){
        i++;
    }
    char * res = malloc(sizeof(char) * (strlen(buf) + 1));
    strcpy(res, buf);
    return res; //?
}

int parser_open_file(struct parser * parser, char * filename){ // открываем файл
    if (filename == NULL) return 0;
    int fp = open(filename, O_RDONLY);
    if (fp < 0){
        perror("opening failed");
        return -1;
    }
    parser->fp_in = fp;
    return fp;
}
