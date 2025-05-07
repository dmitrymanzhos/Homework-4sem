#include "sfml_view.h"
#include <iostream>

SFMLView::SFMLView() {
    m_window.create(sf::VideoMode(800, 600), "Змейка (SFML)");
    m_window.setFramerateLimit(60);
    loadResources();
}

void SFMLView::loadResources() {
    if (!m_snakeTexture.loadFromFile("assets/snake.png")) {
        std::cerr << "Не удалось загрузить текстуру змейки\n";
    }
    if (!m_foodTexture.loadFromFile("assets/food.png")) {
        std::cerr << "Не удалось загрузить текстуру еды\n";
    }
    if (!m_font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Не удалось загрузить шрифт\n";
    }
}

void SFMLView::render() {
    m_window.clear(sf::Color::Black);
    
    drawSnake();
    drawFood();
    drawHUD();
    
    m_window.display();
}

void SFMLView::drawSnake() {
    sf::Sprite segment(m_snakeTexture);
    float cellSize = std::min(
        m_window.getSize().x / m_model->getWidth(),
        m_window.getSize().y / m_model->getHeight()
    );
    
    segment.setScale(cellSize / m_snakeTexture.getSize().x, 
                   cellSize / m_snakeTexture.getSize().y);
    
    for (const auto& coord : m_model->getSnake()->getBody()) {
        segment.setPosition(coord.x * cellSize, coord.y * cellSize);
        m_window.draw(segment);
    }
}

void SFMLView::drawFood() {
    sf::Sprite food(m_foodTexture);
    float cellSize = std::min(
        m_window.getSize().x / m_model->getWidth(),
        m_window.getSize().y / m_model->getHeight()
    );
    
    food.setScale(cellSize / m_foodTexture.getSize().x, 
                cellSize / m_foodTexture.getSize().y);
    
    for (const auto& coord : m_model->getFood()) {
        food.setPosition(coord.x * cellSize, coord.y * cellSize);
        m_window.draw(food);
    }
}

void SFMLView::drawHUD() {
    sf::Text text;
    text.setFont(m_font);
    text.setString("Очки: " + std::to_string(m_model->getScore()));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    m_window.draw(text);
}

void SFMLView::handleInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W: 
                case sf::Keyboard::Up:
                    m_model->changeDirection(Direction::UP);
                    break;
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    m_model->changeDirection(Direction::DOWN);
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    m_model->changeDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    m_model->changeDirection(Direction::RIGHT);
                    break;
                case sf::Keyboard::Escape:
                    m_window.close();
                    break;
            }
        }
    }
}

bool SFMLView::isRunning() const {
    return m_window.isOpen();
}

SFMLView::~SFMLView() {
    m_window.close();
}