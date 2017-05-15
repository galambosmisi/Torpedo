#include "button.hpp"

using namespace std;
using namespace genv;

Button::Button(Window * parent, int x, int y, int sx, int sy, string s, string az)
    : Widget(parent, x,y,sx,sy)
{
    _clickable=true;
    isExtended=false;
    _title=s;
    _ID=az;
    _text.set_color(0,0,0);        //_text.r,_text.g,_text.b
    _back.set_color(255,255,255);       //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);            //_pline.r,_pline.g,_pline.b
    _aline.set_color(255,215,0);        //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

void Button::set_clickable(bool mire)
{

    if(mire==false)
    {
        _back.set_color(224,224,224);
        _pline.set_color(184,184,184);
        _clickable=false;
    }
    if(mire==true)
    {
       _back.set_color(255,255,255);
        _pline.set_color(0,0,0);
        _clickable=true;
    }
}


void Button::draw() const
{
    if(!isExtended || !isActive)
    {
        gout << move_to(_x,_y) << color(_pline.r,_pline.g,_pline.b) << box(_size_x, _size_y);
        gout << move_to(_x+1,_y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-3, _size_y-3);
        gout << move_to(_x+(_size_x-2)/2-gout.twidth(_title)/2, _y+(_size_y-2)/2+5) << color(_text.r,_text.g,_text.b) << text(_title);
    }

    if(isExtended && isActive)
    {

        gout << move_to(_x,_y) << color(_pline.r,_pline.g,_pline.b) << box(_size_x, _size_y);
        gout << move_to(_x+1,_y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-2, _size_y-2);
        gout << move_to(_x+(_size_x)/2-gout.twidth(_title)/2, _y+(_size_y)/2+5) << color(_text.r,_text.g,_text.b) << text(_title);
    }
}

void Button::handle(genv::event ev)
{
    if(_clickable)
    {
        if(ev.button < 0 && ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y + _size_y) isExtended=false;
        if(ev.button > 0 && ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y + _size_y) isExtended=true;
        if(ev.type==ev_mouse && ev.button==btn_left && ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y + _size_y) action();
    }
}

void Button::action() const
 {
     _parent->action(_ID);
 }


string Button::getValue() const
{
    return _title;
}

