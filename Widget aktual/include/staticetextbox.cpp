#include "statictextbox.hpp"
#include "graphics.hpp"
#include <sstream>
using namespace genv;

StaticTextBox::StaticTextBox(Window * parent, int x, int y, int sy, string S, bool asd)
    : Widget(parent,x,y,gout.twidth(S)+8,sy)
{
    _box=asd;
    _s=S;
    _text.set_color(0,0,0);
    _text.set_color(0,0,0);            //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);      //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);           //_pline.r,_pline.g,_pline.b
    _aline.set_color(255,215,0);       //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

StaticTextBox::StaticTextBox(Window * parent, int x, int y, int sx, int sy, string S, bool asd)
    : Widget(parent,x,y,sx,sy)
{
    _box=asd;
    _s=S;
    _text.set_color(0,0,0);
    _text.set_color(0,0,0);            //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);      //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);           //_pline.r,_pline.g,_pline.b
    _aline.set_color(255,215,0);       //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

void StaticTextBox::draw() const
{
        if(_box)
        {
            gout << move_to(_x, _y) << color(_pline.r,_pline.g,_pline.b) << box(_size_x, _size_y);
            gout << move_to(_x+1,_y+1) << color(_back.r,_back.g,_back.b) << box (_size_x-3, _size_y-3);
        }
        gout << color(_text.r,_text.g,_text.b);
        gout << move_to(_x+4, _y+_size_y/2+5) << text(_s);

}

void StaticTextBox::set_text(string s)
{
    _s=s;
}

void StaticTextBox::handle(event ev){}

string StaticTextBox::getValue() const {return _s;}

