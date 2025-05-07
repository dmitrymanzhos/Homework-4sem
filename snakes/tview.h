#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include "view.h"
#include <termios.h>
#include <unistd.h> // Добавляем для STDIN_FILENO

class ConsoleView : public View {
    public:
        ConsoleView();
        ~ConsoleView() override;
        
        void render() override;
        void handleInput() override;
        bool isRunning() const override { return m_running; }

    private:
        bool m_running = true;
        struct termios m_oldTermios;
        
        void setupConsole(); // Только объявление, без реализации
        void restoreConsole();
        void drawBorder() const;
        void drawSnake() const;
        void drawFood() const;
};

#endif