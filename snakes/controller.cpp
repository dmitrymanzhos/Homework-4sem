#include "controller.h"
#include <chrono>
#include <thread>

GameController::GameController(std::unique_ptr<View> view, 
                             std::shared_ptr<GameModel> model)
    : m_view(std::move(view)), m_model(model) {
    m_view->setModel(m_model);
}

void GameController::run() {
    using Clock = std::chrono::high_resolution_clock;
    auto lastTime = Clock::now();
    
    while (m_view->isRunning()) {
        // Рассчёт deltaTime
        auto currentTime = Clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // Ограничиваем максимальное значение deltaTime
        deltaTime = std::min(deltaTime, 0.1f);
        
        // Обновление и отрисовка
        m_view->handleInput();
        m_model->update(deltaTime);
        m_view->render();
        
        // Стабилизация FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}