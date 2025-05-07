// view.cpp
#include "view.h"
#include "tview.h" // для ConsoleView 
#include "sfml_view.h" // для SFMLView

View* View::get_view(int type) {
    if (type == 1) return new ConsoleView();
    if (type == 2) return new SFMLView();
    return nullptr;
}