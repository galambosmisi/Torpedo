#include "player.hpp"
#include "graphics.hpp"
#include "window.hpp"
#include <sstream>
#include <stdlib.h>


using namespace genv;
using namespace std;



Player::Player(Window * parent, string p_id, string p_name, int x, int y) : Window(x,y)
{
    XX=x;
    YY=y;
    life=18;
    _parent=parent;
    player_id=p_id;
    player_name=p_name;
    stx1= new StaticTextBox(this, 515,420,30,"To shoot click on the map", false);
    stx2= new StaticTextBox(this, 105,60,30,"Your fleet", true);
    stx3= new StaticTextBox(this, 497,60,30,"The enemy's fleet", true);
    stx4= new StaticTextBox(this, 356,10,30,player_name, false);
    cout<<gout.twidth(player_name);
    b = new Button(this, 175,420,120,30,"DONE", "nemtalalt");
}

int Player::get_life() const
{
return life;
}

string Player::get_ID()
{
    return player_id;
}

string Player::get_name()
{
    return player_name;
}

void Player::action(string _ID)
{
    if(_ID=="talalt")
    {
        life-=1;

    }
    if(_ID=="nemtalalt")
    {
        set_run(false);
        _parent->action("csere");

    }
    if(_ID=="kattinthato")
    {
        b->set_clickable(true);
        _parent->action("noHand");
    }
    if(_ID=="nemkattinthato")
    {
        b->set_clickable(false);

    }
    if(_ID=="getLife")
    {
        _parent->action("getLife");
    }
}

void Player::event_loop()
{
    event ev;
    gout.open(XX,YY);

    _color _back; //Háttér színe
    _back.set_color(255,255,255);

    //Kirajzolás
    gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
    for (size_t i=0; i<widgets.size(); i++)
    {
        widgets[i]->draw();
    }
    gout << refresh;

    focus=3;
    while(gin >> ev && _run)
    {
        if(ev.keycode==key_escape) exit(0);
        //Sztornó
        gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);

        //Kezelés, nem tudtam rájönni ahibára...Másopdik kör után nem állította a gombra a fokuszt
        if (ev.type == ev_mouse || ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                widgets[i]->handle(ev);
            }
        }

        //Kirajzolás
        for (size_t i=0; i<widgets.size(); i++)
        {
            widgets[i]->draw();
        }

        gout << refresh;
    }
}
