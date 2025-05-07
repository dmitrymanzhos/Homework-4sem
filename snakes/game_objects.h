#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <list>
#include <vector>
#include <unordered_set>
#include <memory>
#include "config.h"

struct Coord {
    int x, y;
    Coord(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Coord& other) const { return x == other.x && y == other.y; }
};

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
    public:
        using Body = std::list<Coord>;
        
        Snake(const Coord& head, Direction dir = Direction::RIGHT);
        virtual ~Snake() = default;
        
        virtual void update(float deltaTime);
        virtual void grow();
        void changeDirection(Direction newDir);
        
        const Body& getBody() const { return m_body; }
        Direction getDirection() const { return m_direction; }

    protected:
        int m_growthPending = 0;
        Body m_body;
        Direction m_direction;
        Direction m_nextDirection;
        float m_moveTimer = 0.0f;
        float m_moveDelay;
        
        virtual Coord calculateNewHead() const;
};

#endif