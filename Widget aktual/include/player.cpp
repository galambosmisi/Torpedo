#include "player.hpp"
#include "graphics.hpp"
#include <sstream>


using namespace genv;
using namespace std;



Player::Player(Window * parent, vector<Ship> s, string p_id, string m_id)
{
    player_id=p_id;
    _m= new Map(parent, 10,10,30,m_id,s);
    _parent=parent;
}
