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

// char * parser_get_word(struct parser * parser) {
//     char buf[32] = {0};  // Инициализируем пустым массивом
//     int c;  // Для хранения результата getchar()
//     int i = 0;

//     while ((c = getc(parser->fp_in)) != EOF) {
//         if (isalpha(c)) {
//             buf[i++] = c;
//             break;
//         }
//     }

//     if (c == EOF) {
//         return NULL;
//     }

//     while ((c = getc(parser->fp_in)) != EOF && isalpha(c) && i < 31) {
//         buf[i++] = c;
//     }

//     buf[i] = '\0';  // Завершаем строку нулевым символом

//     char *res = malloc(sizeof(char) * (i + 1));
//     if (res == NULL) {
//         return NULL;
//     }
//     strcpy(res, buf);
//     return res;
// }
char * parser_get_word(struct parser * parser){
    if(!parser || parser->fp_in == -1) return NULL;

    char buf[32];
    int i = 0;
    ssize_t read_result;

    // Skip non-alpha characters
    do {
        read_result = read(parser->fp_in, buf + i, 1);
        if(read_result <= 0) return NULL; // EOF or error
    } while(!isalpha(buf[i]));

    i++;

    // Read word
    while(i < 31) {  // Leave space for null terminator
        read_result = read(parser->fp_in, buf + i, 1);
        if(read_result <= 0) break;  // EOF or error
        if(!isalpha(buf[i])) break;
        i++;
    }

    buf[i] = '\0';

    char * res = malloc(i + 1);
    if(!res) return NULL;

    strcpy(res, buf);
    return res;
}

int parser_open_file(struct parser * parser, char * filename){
    if(!parser || !filename) return -1;

    // Close previous file if open
    if(parser->fp_in != -1) {
        close(parser->fp_in);
    }

    int fp = open(filename, O_RDONLY);
    if(fp < 0){
        perror("opening failed");
        return -1;
    }
    parser->fp_in = fp;
    return fp;
}