#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "player.hpp"
#include <vector>

using namespace std;

struct koord
{
    int _x, _y;
    bool alive;
    koord();
    koord(int x, int y);
    bool operator== (koord b);

};

struct Ship
{
    vector<koord> pos;
    int max_life;
    bool s_alive;

    Ship(vector<koord> gen_pos, int ml);
    bool isAlive();
    void draw() const;
    bool hor_pos;

};

class Map : public Widget
{
protected:
    string _ID;
    int box_size;
    Window * _enemy;
public:
    int active_x, active_y, life;
    bool draw_ship;
    bool shot;
    bool handleable;
    vector<Ship> ships;
    vector<koord> all_ship_pos;
    vector<vector<bool>> shots;

    Map(Window * parent,  int x, int y, int bs, string ID);
    Map(Window * parent, Window * en, int x, int y, int bs, string ID, vector<Ship> s);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    koord getValue() const ;
    koord getPos() const;
    void newShip(Ship s);
    void setPos(int x, int y);
    bool isShip(int x, int y);
    bool isShip_d(int x, int y) const;
};


#endif // MAP_HPP_INCLUDED
