#ifndef _TVIEW_H_
#define _TVIEW_H_
#include "view.h"

class TView: public View
// class TView
{
    public:
    TView(); // контруктор

    virtual void draw() ; // отрисовка, const override ????
    virtual void run() ; // запуск цикла, event loop

    private:
    int xsize;
    int ysize;

    void clrscr(); // clear screen
    void gotoxy(int x, int y); //go to (x,y)
    void setcolor(const char * color);
    
};


#endif