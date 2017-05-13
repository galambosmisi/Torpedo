#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "window.hpp"
#include "graphics.hpp"

using namespace std;

struct _color
{
    int r, g, b;
    _color();
    virtual void set_color(int _r, int _g, int _b);
};

class Window;

class Widget
{
protected:
    Window * _parent;
    int _x, _y, _size_x, _size_y, ex_size_x, ex_size_y;
    bool isActive = false;
    bool isExtended = false;
    _color _text;
    _color _back;
    _color _pline;
    _color _aline;
public:
    bool doDraw = true;
    Widget(Window * parent, int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y); //vissza adja az isActive értékét
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void set_ex_size();
};


#endif // WIDGETS_HPP_INCLUDED
