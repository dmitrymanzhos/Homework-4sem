#include "model.h"
#include "view.h"
#include <random>
#include <iostream>  
#include <algorithm>


GameModel::GameModel(int width, int height) 
    : m_width(width), m_height(height) {
    m_snake = std::make_unique<Snake>(Coord(width/2, height/2));
    spawnFood();
}

void GameModel::gameOver(const std::string& reason) {
    std::cout << "Game Over: " << reason << "! Очки: " << m_score << "\n";
    // TODO: завершение процессов, восстанавливаем настройки терминала

    if (m_view) {
        if (auto consoleView = dynamic_cast<ConsoleView*>(m_view)) {
            consoleView->restoreConsole();
        }
    }

    exit(0);
}

void GameModel::update(float deltaTime) {
    // 1. Сначала двигаем змейку
    m_snake->update(deltaTime);
    
    Coord head = m_snake->getBody().back();
    
    // 2. Проверяем столкновение с едой
    bool ateFood = false;
    for (auto it = m_food.begin(); it != m_food.end(); ) {
        if (head == *it) {
            m_snake->grow();
            it = m_food.erase(it);
            spawnFood();
            m_score++;
            ateFood = true;
            break;
        } else {
            ++it;
        }
    }
    
    // 3. Проверяем столкновения только если не съели еду
    if (!ateFood) {
        // Со стеной
        if (head.x < 0 || head.y < 0 || head.x >= m_width || head.y >= m_height) {
            gameOver("game over!");
        }
        
        // С собой
        auto body = m_snake->getBody();
        if (std::count(body.begin(), --body.end(), head) > 0) {
            gameOver("game over!");
        }
    }
}

void GameModel::spawnFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, m_width-1);
    std::uniform_int_distribution<> disY(0, m_height-1);
    
    Coord newFood;
    bool positionValid;
    
    do {
        positionValid = true;
        newFood = Coord(disX(gen), disY(gen));
        
        // Проверяем, чтобы еда не появилась на змейке
        for (const auto& segment : m_snake->getBody()) {
            if (segment == newFood) {
                positionValid = false;
                break;
            }
        }
        
        // Проверяем, чтобы не появилась на существующей еде
        for (const auto& food : m_food) {
            if (food == newFood) {
                positionValid = false;
                break;
            }
        }
        
    } while (!positionValid);
    
    m_food.push_back(newFood);
    // std::cout << "Новая еда: (" << newFood.x << "," << newFood.y << ")\n";
}

void GameModel::changeDirection(Direction newDir) {
    if (m_snake) {
        m_snake->changeDirection(newDir);
        // std::cout << "Направление изменено на: " << static_cast<int>(newDir) << std::endl;
    }
}