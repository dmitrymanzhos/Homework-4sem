#include "tview.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <termios.h>

ConsoleView::ConsoleView() {
    // Сохраняем оригинальные настройки терминала
    tcgetattr(STDIN_FILENO, &m_oldTermios);
    
    // Настраиваем новый режим
    struct termios newTermios = m_oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);  // Неканонический режим, без эха
    newTermios.c_cc[VMIN] = 0;   // Не ждём ни одного символа
    newTermios.c_cc[VTIME] = 0;  // Нет таймаута
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
}


ConsoleView::~ConsoleView() {
    restoreConsole();
}

void ConsoleView::setupConsole() {
    tcgetattr(STDIN_FILENO, &m_oldTermios);
    struct termios newTermios = m_oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
}

void ConsoleView::restoreConsole() {
    tcsetattr(STDIN_FILENO, TCSANOW, &m_oldTermios);
}
void ConsoleView::render() {
    std::cout << "\033[2J\033[H";
    drawBorder();
    drawSnake();
    drawFood();
    std::cout.flush();
}

void ConsoleView::drawBorder() const {
    int width = m_model->getWidth();
    int height = m_model->getHeight();
    
    std::cout << "+" << std::string(width, '-') << "+\n";
    for (int y = 0; y < height; ++y) {
        std::cout << "|" << std::string(width, ' ') << "|\n";
    }
    std::cout << "+" << std::string(width, '-') << "+\n";
}

void ConsoleView::drawSnake() const {
    for (const auto& segment : m_model->getSnake()->getBody()) {
        std::cout << "\033[" << (segment.y + 2) << ";" << (segment.x + 2) << "H";
        std::cout << (segment == m_model->getSnake()->getBody().back() ? "@" : "o");
    }
}

void ConsoleView::drawFood() const {
    for (const auto& food : m_model->getFood()) {
        std::cout << "\033[" << (food.y + 2) << ";" << (food.x + 2) << "H";
        std::cout << "*";
    }
}

void ConsoleView::handleInput() {
    struct pollfd fd;
    fd.fd = STDIN_FILENO;
    fd.events = POLLIN;
    
    // Проверяем ввод без блокировки (таймаут 0)
    if (poll(&fd, 1, 0) > 0) {
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            std::cout << "Нажата клавиша: " << c << "\n";  // Отладочный вывод
            
            switch (c) {
                case 'w': 
                case 'W':
                    m_model->changeDirection(Direction::UP);
                    break;
                case 's':
                case 'S':
                    m_model->changeDirection(Direction::DOWN);
                    break;
                case 'a':
                case 'A':
                    m_model->changeDirection(Direction::LEFT);
                    break;
                case 'd':
                case 'D':
                    m_model->changeDirection(Direction::RIGHT);
                    break;
            }
        }
    }
}