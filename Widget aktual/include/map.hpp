#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

using namespace std;

struct koord
{
    int _x, _y;
    bool alive;
    koord();
    koord(int x, int y);
    bool operator== (koord b);

    ostream operator<< (ostream& s);
};

struct Ship
{
    vector<koord> pos;
    int max_life;
    bool alive;
    Ship(vector<koord> gen_pos, int ml);
    bool isAlive();
};

class Map : public Widget
{
protected:
    string _ID;
    int box_size, active_x, active_y;
public:
    vector<Ship> ships;
    vector<koord> all_ship_pos;
    vector<koord> shots;
    Map(Window * parent, int x, int y, int bs, string ID);
    Map(Window * parent, int x, int y, int bs, string ID, vector<Ship> s);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    koord getValue() const ;
    koord getPos() const;
    void newShip(Ship s);
};


#endif // MAP_HPP_INCLUDED
