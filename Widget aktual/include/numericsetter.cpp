#include "numericsetter.hpp"
#include "graphics.hpp"
#include <sstream>

using namespace genv;
using namespace std;

NumericSetter::NumericSetter(Window * parent, int x, int y, int sx, int sy, int mini, int maxi)
    : Widget(parent,x,y,sx,sy)
{
    _min=mini;
    _max=maxi;
    num=mini;
    box_size=_size_y/2;
    _text.set_color(0,0,0);         //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);   //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);  //_pline.r,_pline.g,_pline.b
    _aline.set_color(184,131,11);   //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

string NumericSetter::getValue() const
{
    stringstream ss;
    ss<<num;
    return ss.str();
}

void NumericSetter::draw() const
{
    stringstream ss;
    ss<<num;

    //Keret
    if (isActive) gout << color(_aline.r,_aline.g,_aline.b);
    else gout << color(_pline.r,_pline.g,_pline.b);
    gout << move_to(_x, _y) << box(_size_x, _size_y);
    gout << move_to(_x+1, _y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-2, _size_y-2);

    if (isActive) gout << color(_aline.r,_aline.g,_aline.b);
    else gout << color(_pline.r,_pline.g,_pline.b);
    gout << move_to(_x+_size_x-box_size,_y) << line_to(_x+_size_x-box_size,_y+_size_y-1);
    gout << move_to(_x+_size_x-box_size,_y+box_size) << line_to(_x+_size_x-1,_y+box_size);

    //Szöveg
    gout<<color(_text.r,_text.g,_text.b);
    if (gout.twidth(ss.str())<= _size_x-box_size-8)
    gout << move_to(_x+_size_x-box_size-gout.twidth(ss.str())-4, _y+_size_y/2+5) << text(ss.str());

    //Nyilak
    gout << move_to(_x+_size_x-box_size/2,_y+box_size/2-box_size/4) << line_to(_x+_size_x-box_size/2+box_size/4,_y+box_size/2+box_size/4);
    gout << move_to(_x+_size_x-box_size/2,_y+box_size/2-box_size/4) << line_to(_x+_size_x-box_size/2-box_size/4,_y+box_size/2+box_size/4);
    gout << move_to(_x+_size_x-box_size/2,_y+3*box_size/2+box_size/4) << line_to(_x+_size_x-box_size/2+box_size/4,_y+3*box_size/2-box_size/4);
    gout << move_to(_x+_size_x-box_size/2,_y+3*box_size/2+box_size/4) << line_to(_x+_size_x-box_size/2-box_size/4,_y+3*box_size/2-box_size/4);

}

void NumericSetter::handle(event ev)
{
    if (ev.type == ev_key && ev.keycode == key_up && num!=_max) num++;
    if (ev.type == ev_key && ev.keycode == key_down && num!=_min) num--;
    if (ev.type == ev_key && ev.keycode == key_pgup && num+10<_max) num+=10;
    if (ev.type == ev_key && ev.keycode == key_pgdn && num-10>_min) num-=10;
    if (ev.type == ev_mouse && ev.button==btn_left && ev.pos_x<_x+_size_x-1 && ev.pos_x>_x+_size_x-box_size+1 && ev.pos_y>_y && ev.pos_y<_y+box_size && num!=_max) num++;
    if (ev.type == ev_mouse && ev.button==btn_left && ev.pos_x<_x+_size_x-1 && ev.pos_x>_x+_size_x-box_size+1 && ev.pos_y>_y+box_size && ev.pos_y<_y+2*box_size && num!=_min) num--;
}

