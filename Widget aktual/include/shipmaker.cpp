#include "shipmaker.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

ShipMaker::ShipMaker(Window * parent, Map *m, int x, int y, int bs, int db)
    :Widget(parent,x,y,db*bs,bs)
{
    _m=m;
    hor_pos=true;
    place=false;
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
            gout << move_to(_x+i*(box_size-1)+1,_y+1) << color(_back.r,_back.g,_back.b) << box(box_size-2,box_size-2);
        }

        else
        {
            gout << move_to(_x,_y+i*(box_size-1)) << box(box_size,box_size);
            gout << move_to(_x+1,_y+i*(box_size-1)+1) << color(_back.r,_back.g,_back.b) << box(box_size-2,box_size-2);
        }

    }

}

void ShipMaker::handle(genv::event ev)
{
    if(place) isActive=false;

    if(!place)
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

        //Sz�lek kezel�se
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
                    cout<<_x<<"   "<<_y<<endl;
                }

                if(ev.pos_x > mx && ev.pos_x-1 < mx+11*(box_size-1) && ev.pos_y > my && ev.pos_y-1 < my+11*(box_size-1) && ev.button==btn_left)
                {
                    koord a(i,j);
                    for(int i=0; i<_size; i++)
                    {
                        if(hor_pos) a._x+=i;
                        else a._y+=i;

                        for(int i=0; i<0; i++)
                        {

                        }
                    }

                    place=true;
                }
            }
        }

    }


    if(ev.type==ev_key && ev.keycode==key_space) hor_pos=!hor_pos;

    if(!isActive && !place ) reSet();
}

void ShipMaker::reSet()
{
    _x=px;
    _y=py;
    hor_pos=true;
    place=false;
}