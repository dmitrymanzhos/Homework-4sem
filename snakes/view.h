#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include "model.h"

// Добавляем forward declaration
class ConsoleView;
class SFMLView;


class View {
    public:
        virtual ~View() = default;
        virtual void render() = 0;
        virtual void handleInput() = 0;
        virtual bool isRunning() const = 0;    
        void setModel(std::shared_ptr<GameModel> model) { m_model = model; }
        static View* get_view(int type); 
        // {
        //     if (type == 1) return new ConsoleView(); // класс объявлен в tview.h
        //     // if (type == 2) return new SFMLView(); // класс объявлен в sfml_view.h
        //     return nullptr;
        // }
    protected:
        std::shared_ptr<GameModel> m_model;
}; 

#endif