#include "model.h"

Model::Model()
{
    // int num_rabbits = 5;
    // int num_snakes = 1;
    // int num_segm = 1;

    std::list<rabbit> rabbits;
    std::list<Snake> snakes;
}

void Model::update()
{
    rabbit tmp = {50, 70};
    rabbits.push_back(tmp); //????

}


Snake::Snake(int x, int y, int direction)
{
    int direction = direction;
    segm s = {x, y};

    std::list<segm> body = {s};
}


// Segm::Segm(int x, int y)
// {
//     int x = x;
//     int y = y;
// }