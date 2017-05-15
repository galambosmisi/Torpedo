#include "dynamictextbox.hpp"
#include "graphics.hpp"
#include <iostream>

using namespace genv;
using namespace std;

DynamicTextBox::DynamicTextBox(Window * parent, int x, int y, int sx, int sy, string S, bool asd)
    : StaticTextBox(parent, x,y,sx,sy, S, asd)
{
    _start=S;
    _text.set_color(0,0,0);            //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);      //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);           //_pline.r,_pline.g,_pline.b
    _aline.set_color(0,0,0);         //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

void DynamicTextBox::draw() const
{

    string t=_s;
    if(isActive) t=_s+'|';
    if(isActive)gout << color(_aline.r,_aline.g,_aline.b);
    else gout << color(_pline.r,_pline.g,_pline.b);
    if(_box)
    {
        gout << move_to(_x, _y) << box(_size_x, _size_y);
        gout << move_to(_x+1, _y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-2, _size_y-2);
    }
    gout << color(_text.r,_text.g,_text.b);
    gout << move_to(_x+4, _y+_size_y/2+5) << text(t);


}

void DynamicTextBox::handle(event ev)
{
    if(_s   ==_start && isActive) _s="";
    if(_s == "" && !isActive) _s=_start;

    if (ev.type == ev_key && ev.keycode == key_backspace && _s.size() != 0)
    {
        _s.pop_back();
    }

    string t=_s+'|';
    if (ev.type == ev_key && (31 < ev.keycode && ev.keycode < 256 ) && gout.twidth(t)< _size_x-8)
    {
        _s+=ev.keycode;

    }

    if(ev.type == ev_key && ev.keycode==key_enter && _s != "") _parent->action("player_done");
}

void DynamicTextBox::set_text(string s)
{
    _s=s;
}

string DynamicTextBox::getValue() const
{
    return _s;
}
