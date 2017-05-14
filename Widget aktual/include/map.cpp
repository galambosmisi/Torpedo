#include "map.hpp"
#include "graphics.hpp"
#include <sstream>

using namespace genv;
using namespace std;

Map::Map(Window * parent, int x, int y, int bs, string ID)
    : Widget(parent,x,y,11*bs,11*bs)
{
     active_x=1;
     active_y=1;
    _ID=ID;
    shots.resize(10);
    box_size=bs;
    _text.set_color(0,0,0);             //_text.r,_text.g,_text.b
    _back.set_color(255,255,255);       //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);            //_pline.r,_pline.g,_pline.b
    _aline.set_color(0,35,245);        //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

Map::Map(Window * parent, int x, int y, int bs, string ID, vector<Ship> s)
    : Widget(parent,x,y,11*bs,11*bs)
{
    active_x=1;
    active_y=1;
    ships=s;
    _ID=ID;
    shots.resize(10);
    box_size=bs;
    _text.set_color(0,0,0);             //_text.r,_text.g,_text.b
    _back.set_color(255,255,255);       //_back.r,_back.g,_back.b
    _pline.set_color(0,0,0);            //_pline.r,_pline.g,_pline.b
    _aline.set_color(0,35,245);        //_aline.r,_aline.g,_aline.b
    _parent->push_item(this);
}

koord Map::getValue() const
{
    koord k(active_x-1,active_y-1);
    return k;
}


void Map::draw() const
{
    stringstream ss;
    int korr=10;
    vector<string> betuk = {"A","B","C","D","E","F","G","H","I","J"};
    for(unsigned int i=1; i<11; i++)
    {
        gout << color(_text.r,_text.g,_text.b) << move_to(_x+box_size/2+i*(box_size-1)-gout.twidth(betuk[i-1])/2, _y+box_size-gout.cdescent()-korr) << text(betuk[i-1]);
    }


    for(unsigned int i=1; i<11; i++)
    {
        ss.clear();
        ss.str("");
        ss<<i;
        gout << color(_text.r,_text.g,_text.b) << move_to(_x+box_size-gout.twidth(ss.str())-korr, _y+box_size/2+5+i*(box_size-1)) << text(ss.str());
    }

    for(unsigned int i=1; i<11; i++)
    {
        for(unsigned int j=1; j<11; j++)
        {
            gout << color(_pline.r,_pline.g,_pline.b);
            gout << move_to(_x+i*(box_size-1),_y+j*(box_size-1)) << box(box_size,box_size);
            if(shots[i-1].alive==false) gout << color(243,245,255);
            else gout << color(_back.r,_back.g,_back.b);
            gout << move_to(_x+1+i*(box_size-1),_y+1+j*(box_size-1)) << box(box_size-2,box_size-2);

            /*if(shots[i-1][j-1]==true && isShip)
            {
                gout << color(0,0,0);
                gout << move_to(_x+4+i*(box_size-1), _y+4+j*(box_size-1)) << line(box_size-8, box_size-8);
                gout << move_to(_x+5+i*(box_size-1), _y+4+j*(box_size-1)) << line(box_size-8, box_size-8);
                gout << move_to(_x+box_size-4+i*(box_size-1), _y+4+j*(box_size-1)) << line(-box_size+8, box_size-8);
                gout << move_to(_x+box_size-5+i*(box_size-1), _y+4+j*(box_size-1)) << line(-box_size+8, box_size-8);
            }*/


            if(shots[i-1].alive==false)
            {
                gout << color(0,0,0);
                gout << move_to(_x+box_size/2-2+i*(box_size-1), _y+box_size/2-2+j*(box_size-1)) << box(4,4);
            }
        }
    }


        gout << color(_aline.r,_aline.g,_aline.b) << move_to(_x+active_x*(box_size-1), _y+active_y*(box_size-1)) << line(box_size,0) << line(0,box_size) << line(-box_size,0) << line(0, -box_size);


}

void Map::handle(event ev)
{
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            if(ev.pos_x > _x+i*(box_size-1) && ev.pos_x-1 < _x+(i+1)*(box_size-1) && ev.pos_y > _y+j*(box_size-1) && ev.pos_y-1 < _y+(j+1)*(box_size-1))
            {
                active_x=i;
                active_y=j;
            }

            if(ev.pos_x > _x+i*(box_size-1) && ev.pos_x-1 < _x+(i+1)*(box_size-1) && ev.pos_y > _y+j*(box_size-1) && ev.pos_y-1 < _y+(j+1)*(box_size-1) && ev.button==btn_left)
            {
                 _parent->action(_ID);
            }
        }
    }
}

void Map::newShip(Ship s)
{
    ships.push_back(s);
}

koord Map::getPos() const
{
    koord a(_x,_y);
    return a;
}

koord::koord()
{
    _x=1;
    _y=1;
    alive=true;
}

koord::koord(int x, int y)
{
    _x=x;
    _y=y;
    alive=true;
}

bool koord::operator== (koord b)
{
    return _x==b._x && _y==b._y;
}

bool Ship::isAlive()
{
    int num_of_false=0;
    for(int i=0; i<pos.size(); i++)
    {
        if(pos[i].alive==false) num_of_false+=1;
    }
    if(num_of_false==max_life) alive=false;
    return alive;
}

Ship::Ship(vector<koord> gen_pos, int ml)
{
    alive = true;
    pos=gen_pos;
    max_life=ml;
}
