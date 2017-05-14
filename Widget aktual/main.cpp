#include "graphics.hpp"
#include "widgets.hpp"
#include "window.hpp"
#include "button.hpp"
#include "statictextbox.hpp"
#include "dynamictextbox.hpp"
#include "player.hpp"
#include "map.hpp"
#include "shipmaker.hpp"
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace genv;
using namespace std;

const koord w_poz(840,500);
const koord map_poz1(10,10);
const koord map_poz2(350,10);

class setUpMenu : public Window
{
   public:
    string player_id;
    vector<ShipMaker *> sm;
    vector<Ship> s;
               Map * m;
            Button * b1;
            Button * b2;
    DynamicTextBox * dtx;
     StaticTextBox * stx1;
     StaticTextBox * stx2;
         ShipMaker * sm1;
         ShipMaker * sm2;
         ShipMaker * sm3;
         ShipMaker * sm4;
         ShipMaker * sm5;
         ShipMaker * sm6;
         ShipMaker * sm7;

    setUpMenu(int x, int y, string p_id) : Window(x,y)
    {
        m = new Map(this, 450,90,30, "setUp_map");
       b1 = new Button(this, 565,420,120,30,"Kész","player_done");
       b2 = new Button(this, 95,357,120,30,"Tiszta lap","storno");
      dtx = new DynamicTextBox(this, 395,10,150,30,p_id,true);
     stx1 = new StaticTextBox(this, 295,10,30,"Játkos neve:", false);
     stx2 = new StaticTextBox(this, 10,130,30,"Helyezd el a hajókat:", false);

     sm1  = new ShipMaker(this,m,60,180,30,4);
     sm2  = new ShipMaker(this,m,60,239,30,3);
     sm3  = new ShipMaker(this,m,160,239,30,3);
     sm4  = new ShipMaker(this,m,60,298,30,2);
     sm5  = new ShipMaker(this,m,130,298,30,2);
     sm6  = new ShipMaker(this,m,200,298,30,2);
     sm7  = new ShipMaker(this,m,190,180,30,1);

     sm.push_back(sm1);
     sm.push_back(sm2);
     sm.push_back(sm3);
     sm.push_back(sm4);
     sm.push_back(sm5);
     sm.push_back(sm6);
     sm.push_back(sm7);

     focus=0;
    }

    void action(string _ID)
    {
        if(_ID=="player_done") set_run(false);
        if(_ID=="storno")
        {
            for(int i=0; i<s.size(); i++)
            {
                sm[i]->reSet();
            }
        }
        if(_ID=="setUp_map")
        {
            //s.push_back()
        }

    }

    void event_loop()
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

    while(gin >> ev && _run)
    {
        //Sztornó
        gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);

        //Kattintás, kiválasztás
        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }

        //Kezelés
        if (focus!=-1)
        {
            widgets[focus]->handle(ev);
            widgets[0]->handle(ev);
        }

        //Kirajzolás
        for (size_t i=0; i<widgets.size(); i++)
        {
            widgets[i]->draw();
        }

        gout << refresh;
    }
}
};

class Torpedo : public Window
{
protected:
    Player * p1;
    Player * p2;
    Button * b;
    string active_player="p1";
    bool shot=false;


public:

     Torpedo(int x, int y, vector<Ship> s1, vector<Ship> s2, string player_id1, string player_id2) : Window(x, y)
    {
         b = new Button(this, 175,420,120,30,"Kész","turn_player");
        p1 = new Player(this, s1, player_id1, "click_1");
        p2 = new Player(this, s2, player_id2, "click_2");


    }

    void action(string _ID)
    {
        cout<<_ID<<endl;
        if(_ID=="click_1")
        {
            cout<<"nyehh";
        }
    }

    void event_loop()
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

    while(gin >> ev && _run)
    {
        //Sztornó
        gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);

        //Kattintás, kiválasztás
        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }

        //Kezelés
        if (focus!=-1)
        {
            widgets[focus]->handle(ev);
        }

        //Kirajzolás
        for (size_t i=0; i<widgets.size(); i++)
        {
            widgets[i]->draw();
        }

        gout << refresh;
    }
}
};

int main()
{
    vector<Ship> s1;
    vector<Ship> s2;
    string p_id1;
    string p_id2;

    setUpMenu p1(w_poz._x,w_poz._y, "Player_1");
    p1.event_loop();

    setUpMenu p2(w_poz._x,w_poz._y, "Player_2");
    p2.event_loop();

    Torpedo ablak(w_poz._x,w_poz._y, s1, s2, p_id1, p_id2);
    ablak.event_loop();
    return 0;
}
