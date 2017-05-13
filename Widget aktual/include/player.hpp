#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "graphics.hpp"
#include "map.hpp"

class Player
{
    string player_id;
    Map * _m;
    Window * _parent;
public:

    Player(Window * parent , vector<Ship> s, string p_id, string m_id);

};

#endif // PLAYER_HPP_INCLUDED
