#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tview.h"
#include "view.h"

// View::
TView::TView(): View()
{
    int xsize = 100; // размер экрана
    int ysize = 100; 
    
};


void TView::draw()
{
    struct winsize winsize;

    ioctl(0, TIOCGWINSZ, &winsize); // cчитывание размеров окна
    clrscr();
    gotoxy(winsize.ws_row/2, winsize.ws_col/2-3);
    setcolor("green");

    write(STDOUT_FILENO, "hello!", 7);
    pause();

};

void TView::run()
{
    while(1){
        draw();
        // ...
        getchar();
        // реализация тика
        // sleep();
        // model->update()
    }
}

void TView::clrscr()
{   
    write(STDOUT_FILENO, "\033[H", 4);    // Перемещение курсора в верхний левый угол
    write(STDOUT_FILENO, "\033[J", 4);     // Очистка экрана
    // write(STDOUT_FILENO, "\033[H", 4);    // Перемещение курсора в верхний левый угол
};


void TView::gotoxy(int x, int y)
{
    // проверить x,y
    char line[10];
    sprintf(line, "\033[%d;%dH", x, y);
    write(STDOUT_FILENO, line, sizeof(line));

};


void TView::setcolor(const char * color)
{   
    // write(STDOUT_FILENO, "\033[32m", 5); // green
    write(STDOUT_FILENO, "\033[31m", 5); // red
    
    // switch (color)
    // {
    // case "green":
    //     write(STDOUT_FILENO, "\033[32m", 5);
    //     break;
    
    // default:
        
    //     break;
    // }
}
