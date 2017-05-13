#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

using namespace std;

struct koord
{
    int _x,_y;
    bool alive=true;
    koord();
    koord(int x, int y): _x(x), _y(y) {}
};

struct Ship
{
    vector<koord> pos;
    bool hor_poz = true;
};

class Map : public Widget
{
protected:
    string _ID;
    int box_size, active_x, active_y;
    vector<Ship> ships;
public:
    vector<vector<bool>> shots;

    Map(Window * parent, int x, int y, int bs, string ID);
    Map(Window * parent, int x, int y, int bs, string ID, vector<Ship> s);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    koord getValue() const ;
    //void setPlace(int x, int y);
};


#endif // MAP_HPP_INCLUDED
