#include "game_objects.h"
#include <iostream>

Snake::Snake(const Coord& head, Direction dir) 
    : m_direction(dir), m_nextDirection(dir) {
    m_body.push_back(head);
    m_moveDelay = Config::getInstance().getFloat("snake.speed", 0.2f);
}



void Snake::grow() {
    // Просто увеличиваем счетчик, не добавляя сегменты сразу
    m_growthPending += 1;
}

void Snake::update(float deltaTime) {
    m_moveTimer += deltaTime;
    
    if (m_moveTimer >= m_moveDelay) {
        m_moveTimer = 0;
        m_direction = m_nextDirection;
        
        Coord newHead = calculateNewHead();
        m_body.push_back(newHead);
        
        // Удаляем хвост ТОЛЬКО если не нужно расти
        if (m_growthPending > 0) {
            m_growthPending--;
        } else {
            m_body.pop_front();
        }
    }
}

Coord Snake::calculateNewHead() const {
    Coord head = m_body.back();
    switch (m_direction) {
        case Direction::UP: return Coord(head.x, head.y - 1);
        case Direction::DOWN: return Coord(head.x, head.y + 1);
        case Direction::LEFT: return Coord(head.x - 1, head.y);
        case Direction::RIGHT: return Coord(head.x + 1, head.y);
    }
    return head;
}


void Snake::changeDirection(Direction newDir) {
    // Запрещаем разворот на 180 градусов
    if ((m_direction == Direction::LEFT && newDir != Direction::RIGHT) ||
        (m_direction == Direction::RIGHT && newDir != Direction::LEFT) ||
        (m_direction == Direction::UP && newDir != Direction::DOWN) ||
        (m_direction == Direction::DOWN && newDir != Direction::UP)) {
        m_nextDirection = newDir;
    }
}