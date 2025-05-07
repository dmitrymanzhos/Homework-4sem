#ifndef SFML_VIEW_H
#define SFML_VIEW_H

#include "view.h"
#include <SFML/Graphics.hpp>

class SFMLView : public View {
    public:
        SFMLView();
        ~SFMLView() override;
        
        void render() override;
        void handleInput() override;
        bool isRunning() const override;
        
    private:
        sf::RenderWindow m_window;
        sf::Texture m_snakeTexture;
        sf::Texture m_foodTexture;
        sf::Font m_font;
        
        void loadResources();
        void drawSnake();
        void drawFood();
        void drawHUD();
};

#endif