struct parser;

struct parser * parser_create(); // конструктор
int parser_destroy(struct parser * parser); // деструктор

int parser_open_file(struct parser * parser, char * filename); // открываем файл
char * parser_get_word(struct parser * parser); // считываем одно слово из файла
