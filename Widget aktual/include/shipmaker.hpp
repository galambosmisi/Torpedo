#ifndef SHIPMAKER_HPP_INCLUDED
#define SHIPMAKER_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "map.hpp"

using namespace std;

class ShipMaker : Widget
{
public: //az�rt public minden, mert ez csak a setUpol�shoz kell, k�nnyebb kinyerni az adatokat
    int px, py, box_size, _size, dx, dy;
    bool hor_pos;
    bool place;
    Map * _m;

    ShipMaker(Window * parent, Map *m, int x, int y, int bs, int db);
    void draw() const;
    void handle(genv::event ev);

    void reSet();

};

#endif // SHIPMAKER_HPP_INCLUDED
