#ifndef _VIEW_H_
#define _VIEW_H_


class View // абстрактный класс
{
    public:

    View(); // конструктор
    // virtual ~View(); // деструктор
    static View * getView(const char * type); // 
    virtual void draw(); // const = 0;
    virtual void run(); // const = 0;

};

#endif