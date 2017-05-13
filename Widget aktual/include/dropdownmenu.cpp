#include "dropdownmenu.hpp"
#include "graphics.hpp"
#include <sstream>
#include <vector>
#include <iostream>


using namespace genv;
using namespace std;


DropDownMenu::DropDownMenu(Window * parent, int x, int y, int sx, int sy, int max_i, vector <string>& s)
    : Widget(parent, x,y,sx,sy)
{
    for(unsigned int i=0; i<s.size(); i++)
    {
        items.push_back(s[i]);
    }
    _text.set_color(184,131,11);        //_text.r,_text.g,_text.b
    _back.set_color(200,200,200);       //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);            //_pline.r,_pline.g,_pline.b
    _aline.set_color(255,215,0);        //_aline.r,_aline.g,_aline.b
    max_item=max_i;
    first_item=0;
    box_size=_size_y;
    actual=0;
    if(items.size()-max_item!=0) slider_size=(items.size()-1)*_size_y/(items.size()-1-(max_item-1));
    if(items.size()-max_item==0 || items.size()-max_item==1) slider_size=0;
    _parent->push_item(this);
}

string DropDownMenu::getValue() const
{
    return items[actual];
}

void DropDownMenu::set_ex_size()
{
    ex_size_x=_size_x;
    if(max_item*_size_y  < items.size()*_size_y) ex_size_y=_size_y*(max_item+1);
    else ex_size_y=items.size()*_size_y;
}

void DropDownMenu::draw() const
{
    //Standard keret
    if(isActive) gout << color(_aline.r,_aline.g,_aline.b);
    else gout << color(_pline.r,_pline.g,_pline.b);
    gout << move_to(_x, _y) << box(_size_x, _size_y);
    gout << move_to(_x+1, _y+1) << color(_back.r,_back.g,_back.b) << box(_size_x-2, _size_y-2);

    if(isActive) gout << color(_aline.r,_aline.g,_aline.b);
    else gout << color(_pline.r,_pline.g,_pline.b);
    gout << move_to(_x+_size_x-box_size-1, _y) << line_to(_x+_size_x-box_size-1, _y+box_size-1); //A -1 es eltolások azért vannak, mert a box belső élét színezem

    //Szöveg
    gout<<color(_text.r,_text.g,_text.b);
    string s = "Ures menu";
    if(items.size()!=0) s = items[actual];

    if(gout.twidth(s)>_size_x-box_size-16)  //a két pont mérete miatt -16
    {
        while(gout.twidth(s)>_size_x-box_size-16)
        {
            s.pop_back();
        }
        s+="..";
    }
    gout << move_to(_x+4, _y+_size_y/2+5) << text(s);

    //Nyil
    if(!isExtended)
    {
        gout << move_to(_x+_size_x-box_size/2,_y+box_size/2+box_size/4) << line_to(_x+_size_x-box_size/2+box_size/4,_y+box_size/2-box_size/4);
        gout << move_to(_x+_size_x-box_size/2,_y+box_size/2+box_size/4) << line_to(_x+_size_x-box_size/2-box_size/4,_y+box_size/2-box_size/4);
    }

    int   XX=_size_x-13;
    int   YY=(items.size()-1)*_size_y;
    canvas C;
    C.open(XX+13, YY); //Slider miatt +13
    C.transparent(true);

    //Active keret
    if(isExtended)
    {
        //Nyil
        gout << move_to(_x+_size_x-box_size/2,_y+box_size/2-box_size/4) << line_to(_x+_size_x-box_size/2+box_size/4,_y+box_size/2+box_size/4);
        gout << move_to(_x+_size_x-box_size/2,_y+box_size/2-box_size/4) << line_to(_x+_size_x-box_size/2-box_size/4,_y+box_size/2+box_size/4);

        //Keret
        C << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
        if(isActive) C << color(_aline.r,_aline.g,_aline.b);
        if(!isActive) C << color(_pline.r,_pline.g,_pline.b);
        C << move_to(0,0) << line_to(0,YY) << move_to(XX-1,0) << line_to(XX-1,YY);

        //Szöveg
        stringstream ss;
        int j=0;
        for(unsigned int i=0; i<items.size()-1 && items.size()-1>0; i++)
        {
            ss.clear();
            ss.str("");
            if(i==actual) j++;
            string s = items[j];
            if(gout.twidth(s)>_size_x-box_size-16) //a két pont mérete miatt 16
            {
                while(gout.twidth(s)>_size_x-box_size-16)
                {
                    s.pop_back();
                }
                s+="..";
            }
            ss<<s;
            C << color(_text.r,_text.g,_text.b) << move_to(4,_size_y+i*_size_y-_size_y/2+5) << text(ss.str()); //

            //Keret
            if(isActive) C << color(_aline.r,_aline.g,_aline.b);
            if(!isActive) C << color(_pline.r,_pline.g,_pline.b);
            C << move_to(0,_size_y+i*_size_y-1) << line_to(XX, _size_y+i*_size_y);
            j++;
        }
        //Slider
        if(slider_size>=0)
        {
            if(isActive) C << color(_aline.r,_aline.g,_aline.b);
            if(!isActive) C << color(_pline.r,_pline.g,_pline.b);
            C << move_to(XX,0) << box(13,YY);
            C << move_to(XX,0) << color(_back.r,_back.g,_back.b) << box(12,YY-1);

            if(isActive) C << color(_aline.r,_aline.g,_aline.b);
            if(!isActive) C << color(_pline.r,_pline.g,_pline.b);
            C << move_to(XX, max_item*_size_y-1+first_item*_size_y) << line(13,0);
            C << move_to(XX+1,1+first_item*slider_size) <<  box(10,slider_size-3);
        }

        if(YY <= max_item*_size_y) gout << stamp(C,_x,_y+_size_y);
        if(YY > max_item*_size_y) gout << stamp(C, 0, 0+first_item*_size_y, XX+13, max_item*_size_y, _x,_y+_size_y);
    }



}

void DropDownMenu::handle(event ev)
{
    set_ex_size();
    if(!isActive) isExtended=false;
    if(ev.button < 0) click=false;
    if(ev.button > 0) click=true;
    if(ev.type == ev_mouse && ev.button==btn_left)
    {
        //Extend
        if(!isExtended && ev.pos_x > _x &&  ev.pos_x <_x+_size_x-box_size && ev.pos_y > _y  && ev.pos_y < _y+_size_y)
        {
            isExtended=true;
            first_item=0;
        }
        if(ev.pos_x > _x+_size_x-box_size &&  ev.pos_x <_x+_size_x && ev.pos_y > _y  && ev.pos_y < _y+_size_y)
        {
            isExtended=!isExtended;
            first_item=0;
        }
        //Select
        if(isExtended && ev.pos_x > _x && ev.pos_x < _x+_size_x-box_size)
        {
            int limit;
            if(max_item<items.size()) limit=max_item;
            else limit=items.size();

            for(unsigned int i=0; i<=limit && limit>0; i++)
            {
                if(ev.pos_y >_y+_size_y+i*_size_y && ev.pos_y < _y+_size_y+(i+1)*_size_y)
                {
                    if(actual<=i+first_item) i++;
                    actual=i+first_item;
                    isExtended=!isExtended;
                }
            }
        }
        //Scroll
        if(isExtended && ev.pos_x > _x+_size_x-13 && ev.pos_x < _x+_size_x && items.size()-1-(max_item-1)>0)
        {
            double _size=(max_item*_size_y)/(items.size()-1-(max_item-1));
            for(unsigned int i=0; i<items.size()-1-(max_item-1); i++)
            {
                if(ev.pos_y >= _y+_size_y+i*_size && ev.pos_y <= _y+_size_y+(i+1)*_size) first_item=i;
                if(i > items.size()-max_item-1) first_item=items.size()-max_item-1;
            }
        }
    }
    //scroll
    if(click && ev.button!=btn_wheeldown && ev.button!=btn_wheelup && items.size()-1-(max_item-1)>0)
    {
        int _size=(max_item*_size_y)/(items.size()-1-(max_item-1));
        for(unsigned int i=0; i<items.size()-1-(max_item-1); i++)
        {
            if(ev.pos_y > _y+_size_y+i*_size && ev.pos_y < _y+_size_y+(i+1)*_size) first_item=i;
        }
    }
    if (ev.type == ev_mouse && ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y <_y+_size_y+max_item*_size_y && ev.pos_y > _y)
    {
        if(ev.button == btn_wheelup && first_item!=items.size()-max_item-1) first_item+=1;
        if(ev.button == btn_wheeldown && first_item!=0) first_item-=1;
    }
    if(isExtended)
    {
        if(ev.type==ev_key && ev.keycode==key_up && first_item!=0) first_item-=1;
        if(ev.type==ev_key && ev.keycode==key_down && first_item!=items.size()-max_item-1) first_item+=1;
    }
}

void DropDownMenu::add_answer(string s)
{
    items.push_back(s);
    set_ex_size();
    if(items.size()-max_item!=0) slider_size=(items.size()-1)*_size_y/(items.size()-1-(max_item-1));
    if(items.size()-max_item==0 || items.size()-max_item==1) slider_size=0;
}

void DropDownMenu::delet_actual_answer()
{
    if(items.size()!=0) items.erase(items.begin()+actual);
    set_ex_size();
    if(items.size()-max_item!=0) slider_size=(items.size()-1)*_size_y/(items.size()-1-(max_item-1));
    if(items.size()-max_item==0 || items.size()-max_item==1) slider_size=0;
    if(actual > items.size()-1) actual=items.size()-1;
}
