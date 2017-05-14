#ifndef SHIPMAKER_HPP_INCLUDED
#define SHIPMAKER_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "map.hpp"

using namespace std;

class ShipMaker : Widget
{
public: //azért public minden, mert ez csak a setUpoláshoz kell, könnyebb kinyerni az adatokat
    int px, py, box_size, _size, dx, dy;
    bool hor_pos;
    bool place;
    Map * _m;
    vector<koord> _pos;
    string _ID;
    string comp_ID;

    ShipMaker(Window * parent, Map *m, int x, int y, int bs, int db, string id);
    void draw() const;
    void handle(genv::event ev);
    void reSet();
    void makeKoord(int i, int j);
    void makeKoord();

};

#endif // SHIPMAKER_HPP_INCLUDED
