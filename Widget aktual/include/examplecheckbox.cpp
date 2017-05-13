#include "examplecheckbox.hpp"
#include "graphics.hpp"
#include <sstream>

using namespace genv;

CheckBox::CheckBox(Window* parent, int x, int y, int sx, int sy)
    : Widget(parent, x,y,sx,sy)
{
    _checked=false;
    _text.set_color(0,0,0);            //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);      //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);           //_pline.r,_pline.g,_pline.b
    _aline.set_color(255,215,0);       //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

void CheckBox::draw() const
{
    gout << color(_pline.r,_pline.g,_pline.b);
    gout << move_to(_x, _y) << box(_size_x, _size_y);
    gout << move_to(_x+1, _y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-2, _size_y-2);
    if (_checked) {
        gout << color(_text.r,_text.g,_text.b);
        gout << move_to(_x+4, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+5, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+_size_x-4, _y+4) << line(-_size_x+8, _size_y-8);
        gout << move_to(_x+_size_x-5, _y+4) << line(-_size_x+8, _size_y-8);
    }
}

void CheckBox::handle(event ev)
{
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ')) {
            _checked = !_checked;
    }
    if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
        _checked = !_checked;
    }
}
bool CheckBox::is_checked() const
{
    return _checked;
}

string CheckBox::getValue() const
{
   string s;
   if(_checked) s="checked";
   else s="unchecked";
   return s;
}
