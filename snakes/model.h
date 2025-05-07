#ifndef MODEL_H
#define MODEL_H

// #include "view.h"
#include <memory>
#include <vector>
#include "game_objects.h"

class ConsoleView;

class GameModel {
    public:
        GameModel(int width, int height);
        int getScore() const { return m_score; };

        void update(float deltaTime);
        void changeDirection(Direction newDir);
        
        const std::unique_ptr<Snake>& getSnake() const { return m_snake; };
        const std::vector<Coord>& getFood() const { return m_food; };
        int getWidth() const { return m_width; };
        int getHeight() const { return m_height; };

        void setView(View* view) { m_view = view; };

    private:

        int m_width;
        int m_height;
        std::unique_ptr<Snake> m_snake;
        std::vector<Coord> m_food;
        int m_score = 0;
        void gameOver(const std::string& reason); 
        
        void spawnFood();
    
    protected:
        View* m_view = nullptr;
};

#endif