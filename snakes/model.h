#ifndef _MODEL_H_
#define _MODEL_H_

#include <list> // Подключаем заголовочный файл для std::list
#include <string> // Пример использования строк

class Model
{
    public:
    Model();
    static void update();
    std::list<rabbit> rabbits;
    std::list<Snake> snakes;
};

class Snake
{
    public:
    Snake(int x, int y, int direction);
    std::list<segm> body;
    int direction;
};

// class Segm
// {
//     public:
//     Segm(int x, int y);
//     int x;
//     int y;
// };

// class Rabbit
// {   
//     public:
//     Rabbit(int x, int y);
//     int x;
//     int y;
// };

typedef struct segm{
    int x;
    int y;
} segm;

typedef struct rabbit{
    int x;
    int y;
 } rabbit;


#endif
