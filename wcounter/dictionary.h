struct all_words;

struct all_words * dictionary_create(); // конструктор
int dictionary_destroy(struct all_words * all_words); // деструктор

struct all_words * dictionary_append(struct all_words * all_words, char * word); // добавить слово
struct all_words * dictionary_sort(struct all_words * all_words); // сортировка
struct all_words * dictionary_print(struct all_words * all_words); // печать

// struct all_words * dictionary_change(char * word); // изменить количество слов