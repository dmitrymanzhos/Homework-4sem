#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "view.h"
#include "model.h"

class GameController {
    public:
        GameController(std::unique_ptr<View> view, std::shared_ptr<GameModel> model);
        void run();

    private:
        std::unique_ptr<View> m_view;
        std::shared_ptr<GameModel> m_model;
};

#endif