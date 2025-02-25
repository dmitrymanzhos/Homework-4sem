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

struct parser * parser_create(){
    struct parser * parser = malloc(sizeof(struct parser));
    if(!parser) return NULL;
    *parser = (struct parser){-1};
    return parser;
}

int parser_destroy(struct parser * parser){
    if(!parser) return -1;
    if(parser->fp_in != -1) {
        close(parser->fp_in);
    }
    free(parser);
    return 0;
}

char * parser_get_word(struct parser * parser) {
    if (!parser || parser->fp_in == -1) return NULL;

    char buf[32];
    int i = 0;
    while (read(parser->fp_in, buf + i, 1) > 0) {
        if (isalpha(buf[i]))
            break;
    }
    if (!isalpha(buf[i]))
        return NULL;
    i++;
    while (i < 31) {
        if (read(parser->fp_in, buf + i, 1) <= 0 || !isalpha(buf[i]))
            break;
        i++;
    }
    buf[i] = '\0';
    char *res = malloc(i + 1);
    if (!res) {
        perror("malloc");
        return NULL;
    }

    strcpy(res, buf);
    return res;
}

int parser_open_file(struct parser * parser, char * filename) {
    if (!parser) 
        return -1;
    if(filename == NULL){
        parser->fp_in = 0;
        return 0;
    }
    if (parser->fp_in != -1) {
        close(parser->fp_in);
    }

    int fp = open(filename, O_RDONLY);
    if (fp < 0) {
        perror("Failed to open file");
        return -1;
    }
    parser->fp_in = fp;
    return 0;
}