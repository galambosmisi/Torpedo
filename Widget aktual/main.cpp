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
    vector<ShipMaker *> sm; //reSet() függvény egyszerűbb meghívása miatt
    bool start=false;

    Map * m;
    Button * b1;
    Button * b2;
    DynamicTextBox * dtx;
    StaticTextBox * stx1;
    StaticTextBox * stx2;
    StaticTextBox * stx3;
    ShipMaker * sm1;
    ShipMaker * sm2;
    ShipMaker * sm3;
    ShipMaker * sm4;
    ShipMaker * sm5;
    ShipMaker * sm6;
    ShipMaker * sm7;
    ShipMaker * sm8;

    setUpMenu(int x, int y, string p_id) : Window(x,y)
    {
        player_id=p_id;

        m = new Map(this, 450,90,30, "setUp_map");
        b1 = new Button(this, 565,420,120,30,"Done","player_done");
        b2 = new Button(this, 95,357,120,30,"Reset","storno");
        dtx = new DynamicTextBox(this, 395,10,150,30,p_id,true);
        stx1 = new StaticTextBox(this, 290,10,30,"Player name:", false);
        stx2 = new StaticTextBox(this, 75,110,30,"Place all your ships:", false);
        stx3 = new StaticTextBox(this, 35,130,30,"To rotate press the 'space' key", false);

        sm1  = new ShipMaker(this,m,60,180,30,4,"1");
        sm2  = new ShipMaker(this,m,60,239,30,3,"2");
        sm3  = new ShipMaker(this,m,172,239,30,3,"3");
        sm4  = new ShipMaker(this,m,60,298,30,2,"4");
        sm5  = new ShipMaker(this,m,130,298,30,2,"5");
        sm6  = new ShipMaker(this,m,200,298,30,2,"6");
        sm7  = new ShipMaker(this,m,190,180,30,1,"7");
        sm8  = new ShipMaker(this,m,230,180,30,1,"8");

        sm.push_back(sm1);
        sm.push_back(sm2);
        sm.push_back(sm3);
        sm.push_back(sm4);
        sm.push_back(sm5);
        sm.push_back(sm6);
        sm.push_back(sm8);

        focus=0;
    }

    bool all_placed()
    {
        bool asd=true;
        for(int i=0; i<sm.size(); i++)
        {
            if(sm[i]->placed==false) asd=false;
        }
        return asd;
    }


    bool cmp (vector<koord> k)
    {
        bool asd=true;
        cout<<endl<<"Osszehasonlitas: "<<endl;
        for(int i=0; i<m->all_ship_pos.size(); i++)
        {
            cout<<endl<<i<< ". alap elem:";
            for(int j=0; j<k.size(); j++)
            {
                cout<<endl<<"Eddigi: "<<m->all_ship_pos[i]._x<<"   "<<m->all_ship_pos[i]._y;
                cout<<endl<<"  Most: "<<k[j]._x<<"   "<<k[j]._y;
                if(m->all_ship_pos[i]==k[j]) asd=false;
                cout<<endl<<" Ertek: "<<asd;
                if(asd==false) break;


            }
            cout<<endl;
            if(asd==false) break;
        }

        cout<<endl<<"Eredmeny: "<<asd<<endl<<endl;
        return asd;
    }

    void action(string _ID)
    {
        cout<<"Beerkezett _ID: "<<_ID<<"  |"<<endl;;
        if(_ID=="player_done")
        {

            if(all_placed()) set_run(false);
            cout<<endl<<"Elnek-e: "<<endl;
            for(int i=0; i<sm.size(); i++)
            {
                cout<<sm[i]->placed<<endl;
            }
            cout<<endl;
        }

        if(_ID=="storno")
        {
            m->all_ship_pos.clear();
            for(int i=0; i<sm.size(); i++)
            {
                sm[i]->reSet();
            }
        }

        if(_ID=="1")
        {
            Ship ms(sm1->_pos, sm1->box_size);
            m->newShip(ms);
        }
        if(_ID=="2")
        {
            Ship ms(sm2->_pos, sm2->box_size);
            m->newShip(ms);
        }
        if(_ID=="3")
        {
            Ship ms(sm3->_pos, sm3->box_size);
            m->newShip(ms);
        }
        if(_ID=="4")
        {
            Ship ms(sm4->_pos, sm4->box_size);
            m->newShip(ms);
        }
        if(_ID=="5")
        {
            Ship ms(sm5->_pos, sm5->box_size);
            m->newShip(ms);
        }
        if(_ID=="6")
        {
            Ship ms(sm6->_pos, sm6->box_size);
            m->newShip(ms);
        }
        if(_ID=="7")
        {
            Ship ms(sm7->_pos, sm7->box_size);
            m->newShip(ms);
        }

        if(_ID=="cmp1" && cmp(sm1->_pos))
        {
            sm1->placed=true;
            sm1->makeKoord();
        }
        if(_ID=="cmp2" && cmp(sm2->_pos))
        {
            sm2->placed=true;
            sm2->makeKoord();
        }
        if(_ID=="cmp3" && cmp(sm3->_pos))
        {
            sm3->placed=true;
            sm3->makeKoord();
        }
        if(_ID=="cmp4" && cmp(sm4->_pos))
        {
            sm4->placed=true;
            sm4->makeKoord();
        }
        if(_ID=="cmp5" && cmp(sm5->_pos))
        {
            sm5->placed=true;
            sm5->makeKoord();
        }
        if(_ID=="cmp6" && cmp(sm6->_pos))
        {
            sm6->placed=true;
            sm6->makeKoord();
        }
        if(_ID=="cmp7" && cmp(sm7->_pos))
        {
            sm7->placed=true;
            sm7->makeKoord();
        }
    }

    void event_loop()
    {
        event ev;

        gout.open(XX,YY);

        _color _back; //Háttér színe
        _back.set_color(255,255,255);


        //welcome
        string s1, s2, s0;
        s0="Hello!";
        s1="You are "+player_id;
        s2="Please press 'enter' to start building your fleet.";
        gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
        gout<<move_to(w_poz._x/2-gout.twidth(s0)/2, w_poz._y/2-2*((gout.cascent()+gout.cdescent())/2+10)) << color(0,0,0) << text(s0);
        gout<<move_to(w_poz._x/2-gout.twidth(s1)/2, w_poz._y/2-((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s1);
        gout<<move_to(w_poz._x/2-gout.twidth(s2)/2, w_poz._y/2+((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s2);

        gout << refresh;

        while(gin >> ev && _run)
        {
            //Sztornó
            gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);


            if(ev.type==ev_key && ev.keycode==key_enter) start=true;

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
            if (focus!=-1 && start)
            {
                widgets[focus]->handle(ev);
                widgets[0]->handle(ev);
            }

            //Kirajzolás
            for (size_t i=0; i<widgets.size() && start; i++)
            {
                widgets[i]->draw();
            }

            if(!start)
            {
                gout<<move_to(w_poz._x/2-gout.twidth(s0)/2, w_poz._y/2-2*((gout.cascent()+gout.cdescent())/2+10)) << color(0,0,0) << text(s0);
                gout<<move_to(w_poz._x/2-gout.twidth(s1)/2, w_poz._y/2-((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s1);
                gout<<move_to(w_poz._x/2-gout.twidth(s2)/2, w_poz._y/2+((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s2);
            }


            gout << refresh;
        }
    }
};

class Torpedo : public Window
{
protected:

    bool player_changed=false;
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

    void change_player()
    {
        player_changed=!player_changed;
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
    s1=p1.m->ships;
    p_id1=p1.player_id;

    setUpMenu p2(w_poz._x,w_poz._y, "Player_2");
    p2.event_loop();
    s2=p2.m->ships;
    p_id2=p2.player_id;

    Torpedo ablak(w_poz._x,w_poz._y, s1, s2, p_id1, p_id2);
    ablak.event_loop();
    return 0;
}
