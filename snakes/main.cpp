#include <iostream>
#include <memory>
#include "config.h"
#include "model.h"
#include "view.h"
#include "tview.h"  // Подключаем заголовок консольного представления
#include "controller.h"

int main() {
    std::cout << "Выберите режим:\n"
              << "1. Консольный\n"
              << "2. Графический (SFML)\n";
    
    int choice;
    std::cin >> choice;
    
    Config::getInstance().loadFromFile("config.ini");
    auto model = std::make_shared<GameModel>(
        Config::getInstance().getInt("game.width", 60),
        Config::getInstance().getInt("game.height", 30)
    );
    
    auto view = std::unique_ptr<View>(View::get_view(choice));
    if (!view) {
        std::cerr << "Неверный выбор режима\n";
        return 1;
    }
    
    view->setModel(model);
    model->setView(view.get());
    GameController controller(std::move(view), model);
    controller.run();
    
    return 0;
}