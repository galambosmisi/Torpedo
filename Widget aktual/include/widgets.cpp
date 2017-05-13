#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;

_color::_color()
{
    r=255;
    g=255;
    b=255;
}

void _color::set_color(int _r, int _g, int _b)
{
    r=_r;
    g=_g;
    b=_b;
}

Widget::Widget(Window * parent, int x, int y, int sx, int sy)
{
    _parent=parent;
    _x=x;
    _y=y;
    _size_x = sx;
    _size_y = sy;
    bool isActive = false;
}

bool Widget::is_selected(int mouse_x, int mouse_y)
{
    isActive=false;
    if(!isExtended && mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y) isActive=true;
    if(isExtended && mouse_x>_x && mouse_x<_x+ex_size_x && mouse_y>_y && mouse_y<_y+ex_size_y) isActive=true;
    return isActive;
}


void Widget::draw() const{}

void Widget::handle(event ev){}

void Widget::set_ex_size(){}


