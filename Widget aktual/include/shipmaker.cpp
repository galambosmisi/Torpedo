#include "shipmaker.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

ShipMaker::ShipMaker(Window * parent, Map *m, int x, int y, int bs, int db, string id)
    :Widget(parent,x,y,db*bs,bs)
{
    _ID=id;
    comp_ID="cmp"+id;
    _m=m;
    hor_pos=true;
    placed=false;
    px=x;
    py=y;
    _size=db;
    box_size=bs;
    _text.set_color(0,0,0);             //_text.r,_text.g,_text.b
    _back.set_color(155,208,255);       //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);            //_pline.r,_pline.g,_pline.b
    _aline.set_color(0,35,245);        //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

void ShipMaker::draw() const
{


    for(int i=0; i<_size; i++)
    {
        if(isActive) gout << color(_aline.r,_aline.g,_aline.b);
        else  gout << color(_pline.r,_pline.g,_pline.b);
        if(hor_pos)
        {
            gout << move_to(_x+i*(box_size-1),_y) << box(box_size,box_size);
            if(i==0)        gout << move_to(_x+i*(box_size-1)+2,_y+2) << color(_back.r,_back.g,_back.b) << box(box_size-3,box_size-4);
            if(i==_size-1)  gout << move_to(_x+i*(box_size-1)+1,_y+2) << color(_back.r,_back.g,_back.b) << box(box_size-3,box_size-4);
            if(i!= 0 && i!=_size-1)  gout << move_to(_x+i*(box_size-1)+1,_y+2) << color(_back.r,_back.g,_back.b) << box(box_size-2,box_size-4);
        }

        else
        {
            gout << move_to(_x,_y+i*(box_size-1)) << box(box_size,box_size);
            if(i==0)                gout << move_to(_x+2,_y+i*(box_size-1)+2) << color(_back.r,_back.g,_back.b) << box(box_size-4,box_size-3);
            if(i==_size-1)          gout << move_to(_x+2,_y+i*(box_size-1)+1) << color(_back.r,_back.g,_back.b) << box(box_size-4,box_size-3);
            if(i!= 0 && i!=_size-1) gout << move_to(_x+2,_y+i*(box_size-1)+1) << color(_back.r,_back.g,_back.b) << box(box_size-4,box_size-2);
        }

        if(_size==1)
        {
           if(isActive) gout << color(_aline.r,_aline.g,_aline.b);
            else  gout << color(_pline.r,_pline.g,_pline.b);
            gout << move_to(_x,_y) << box(box_size,box_size);
            gout << move_to(_x+2,_y+2) << color(_back.r,_back.g,_back.b) << box(box_size-4,box_size-4);
        }

    }

}

void ShipMaker::handle(genv::event ev)
{
    if(placed) isActive=false;

    if(!placed)
    {
        if(isActive && ev.type==ev_mouse && ev.button==btn_left)
        {
            dx=ev.pos_x-_x;
            dy=ev.pos_y-_y;
        }

        if(isActive && ev.type==ev_mouse)
        {
            _x+=ev.pos_x-dx-_x;
            _y+=ev.pos_y-dy-_y;
        }

        //Szélek kezelése
        if(!(_x+_size*box_size<=_parent->XX)) _x=_parent->XX-_size*box_size;
        if(!(_x>0)) _x=0;
        if(!(_y+box_size<=_parent->YY))_y=_parent->YY-box_size;
        if(!(_y>0))_y=0;

        int mx=_m->getPos()._x;
        int my=_m->getPos()._y;
        int i_lim;
        int j_lim;

        if(hor_pos)
        {
            i_lim=11-_size;
            j_lim=11;
        }
        else
        {
            i_lim=11;
            j_lim=11-_size;
        }

        for(int i=1; i<11; i++)
        {
            for(int j=1; j<11; j++)
            {
                if(ev.pos_x > mx+i*(box_size-1) && ev.pos_x-1 < mx+(i+1)*(box_size-1) && ev.pos_y > my+j*(box_size-1) && ev.pos_y-1 < my+(j+1)*(box_size-1))
                {
                    _x=mx+i*(box_size-1);
                    _y=my+j*(box_size-1);
                    if(i>i_lim) _x=mx+=i_lim*(box_size-1);
                    if(j>j_lim) _y=my+=j_lim*(box_size-1);
                    if(ev.button==btn_left && !placed)
                    {
                        if(hor_pos && i>11-_size) i=11-_size;
                        if(!hor_pos && j>11-_size) j=11-_size;
                        makeKoord(i,j);
                        _parent->action(comp_ID);
                        if(placed==true) _parent->action(_ID);
                    }
                }
            }
        }
    }


    if(ev.type==ev_key && ev.keycode==key_space && !placed) hor_pos=!hor_pos;

    if(!isActive && !placed ) reSet();
}

void ShipMaker::reSet()
{
    _x=px;
    _y=py;
    hor_pos=true;
    placed=false;
}

void ShipMaker::makeKoord(int i, int j)
{
    _pos.clear();
    koord a(i,j);
    _pos.push_back(a);
    for(int i=1; i<_size; i++)
    {
        if(hor_pos) a._x+=1;
        if(!hor_pos) a._y+=1;
        _pos.push_back(a);
    }
}

void ShipMaker::makeKoord()
{
    for(int i=0; i<_pos.size(); i++)
    {
        _m->all_ship_pos.push_back(_pos[i]);

    };
}
