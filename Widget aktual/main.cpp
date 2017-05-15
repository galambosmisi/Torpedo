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
const koord map_poz1(60,90);
const koord map_poz2(450,90);


class setUpMenu : public Window
{
public:
    string player_id;
    string player_name;
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
        sm.push_back(sm7);
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
        for(int i=0; i<m->all_ship_pos.size(); i++)
        {
            for(int j=0; j<k.size(); j++)
            {
                if(m->all_ship_pos[i]==k[j]) asd=false;
                if(asd==false) break;


            }
            if(asd==false) break;
        }
        return asd;
    }

    void action(string _ID)
    {
        if(_ID=="player_done")
        {

            if(all_placed()) set_run(false);
            player_name=dtx->getValue();
        }

        if(_ID=="storno")
        {
            for(int i=0; i<sm.size(); i++)
            {
                sm[i]->reSet();
            }
            m->all_ship_pos.clear();
            m->ships.clear();

        }

        if(_ID=="1")
        {
            Ship ms(sm1->_pos, sm1->_size);
            m->newShip(ms);
        }
        if(_ID=="2")
        {
            Ship ms(sm2->_pos, sm2->_size);
            m->newShip(ms);
        }
        if(_ID=="3")
        {
            Ship ms(sm3->_pos, sm3->_size);
            m->newShip(ms);
        }
        if(_ID=="4")
        {
            Ship ms(sm4->_pos, sm4->_size);
            m->newShip(ms);
        }
        if(_ID=="5")
        {
            Ship ms(sm5->_pos, sm5->_size);
            m->newShip(ms);
        }
        if(_ID=="6")
        {
            Ship ms(sm6->_pos, sm6->_size);
            m->newShip(ms);
        }
        if(_ID=="7")
        {
            Ship ms(sm7->_pos, sm7->_size);
            m->newShip(ms);
        }
        if(_ID=="8")
        {
            Ship ms(sm8->_pos, sm8->_size);
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
        if(_ID=="cmp8" && cmp(sm8->_pos))
        {
            sm8->placed=true;
            sm8->makeKoord();
        }
    }

    void event_loop()
    {
        event ev;
        cout<<"To shoot click on the map:  "<<gout.twidth("To shoot click on the map")<<endl;
        cout<<"Your fleet:  "<<gout.twidth("Your fleet")<<endl;
        cout<<"The enemy's fleet:  "<<gout.twidth("The enemy's fleet")<<endl;
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
        gin.timer(10);
        while(gin >> ev && _run)
        {
            if(ev.keycode==key_escape) exit(0);
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

class Torpedo : Window
{
protected:
    string winner;

    Player * p1;
    string player_1_ID;
    Map * p1_map;
    Player * p2;
    string player_2_ID;
    Map * p2_map;

    Player * active;
    Button * b;
    bool shot=false;
    bool game_on=false;
    bool setUp_on=true;
    bool player_changed=true;
    bool game_end=false;

public:


    Torpedo(int x, int y) : Window(x,y) {}

    void change_player(string p)
    {
        if(p=="p1")
        {
            p1->action("nemkattinthato");
            p1_map->draw_ship=true;
            p1_map->shot=false;
            p1_map->setPos(map_poz1._x,map_poz1._y);
            p1_map->life=p1->get_life();
            p2_map->draw_ship=false;
            p2_map->shot=true;
            p2_map->handleable=true;
            p2_map->setPos(map_poz2._x,map_poz2._y);
            active=p1;
        }

        if(p=="p2")
        {
            p2->action("nemkattinthato");
            p2_map->draw_ship=true;
            p2_map->shot=false;
            p2_map->setPos(map_poz1._x,map_poz1._y);
            p2_map->life=p2->get_life();
            p1_map->draw_ship=false;
            p1_map->shot=true;
            p1_map->handleable=true;
            p1_map->setPos(map_poz2._x,map_poz2._y);
            active=p2;
        }
        player_changed=false;
    }

    void action(string _ID)
    {
        if(_ID=="csere" && player_changed)
        {
            if(active==p1 && player_changed) change_player("p2");
            if(active==p2 && player_changed) change_player("p1");
        }
        if(_ID=="noHand")
        {
            if(active==p1) p2_map->handleable=false;
            if(active==p2) p1_map->handleable=false;
        }
        if(_ID=="getLife")
        {
            if(active==p1) p2_map->life=p2->get_life();
            if(p2->get_life()==0)
            {
                game_on=false;
                game_end=true;
                winner=p1->get_name();
                p1->set_run(false);
                p2->set_run(false);
            }
            if(active==p2) p1_map->life=p1->get_life();
            if(p1->get_life()==0)
            {
                game_on=false;
                game_end=true;
                winner=p2->get_name();
                p1->set_run(false);
                p2->set_run(false);
            }
        }
    }


    void game()
    {
        event ev;

        gout.open(XX,YY);

        _color _back; //Háttér színe
        _back.set_color(255,255,255);

        gin.timer(20);

        while(gin >> ev && _run && ev.keycode!=key_escape )
        {


            if(setUp_on)
            {
                setUpMenu sm_p1(w_poz._x,w_poz._y, "Player_1");
                sm_p1.event_loop();

                setUpMenu sm_p2(w_poz._x,w_poz._y, "Player_2");
                sm_p2.event_loop();

                p1 = new Player(this, sm_p1.player_id, sm_p1.player_name,w_poz._x,w_poz._y);
                p2 = new Player(this, sm_p2.player_id, sm_p2.player_name,w_poz._x,w_poz._y);

                p1_map = new Map(p1,p2, 60,90,30, "map_1", sm_p1.m->ships);
                p2_map = new Map(p2,p1, 60,90,30, "map_2", sm_p2.m->ships);

                change_player("p1");
                setUp_on=false;
            }




            if(!game_on && !game_end )
            {
                string s1, s2;
                s1=p1->get_name()+" start the game ";
                s2="Please press 'enter' to begin the war.";
                gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
                gout<<move_to(w_poz._x/2-gout.twidth(s1)/2, w_poz._y/2-((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s1);
                gout<<move_to(w_poz._x/2-gout.twidth(s2)/2, w_poz._y/2+((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s2);
                if(ev.type==ev_key && ev.keycode==key_enter)
                {
                    player_changed=true;
                    game_on=true;
                }
            }


            if(!game_on && game_end)
            {
                string s1, s2;
                s1="The winner is: "+winner;
                s2="Please press 'esc' to end the war.";
                gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
                gout<<move_to(w_poz._x/2-gout.twidth(s1)/2, w_poz._y/2-((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s1);
                gout<<move_to(w_poz._x/2-gout.twidth(s2)/2, w_poz._y/2+((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s2);
                if(ev.type==ev_key && ev.keycode==key_escape)
                {
                    _run=false;
                }
            }


            if(!player_changed )
            {
                string s1, s2;
                s1="Now time to change";
                s2="Please press 'enter' to continue if your name: "+active->get_name();
                gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
                gout<<move_to(w_poz._x/2-gout.twidth(s1)/2, w_poz._y/2-((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s1);
                gout<<move_to(w_poz._x/2-gout.twidth(s2)/2, w_poz._y/2+((gout.cascent()+gout.cdescent())/2+5)) << color(0,0,0) << text(s2);
                if(ev.type==ev_key && ev.keycode==key_enter) player_changed=true;
            }

            if(game_on && player_changed)
            {
                active->set_run(true);
                active->event_loop();

            }
            gout << refresh;
            gout << move_to(0,0) << color(_back.r,_back.g,_back.b) << box(XX,YY);
        }

    }
};


int main()
{

    Torpedo torpedo(w_poz._x,w_poz._y);
    torpedo.game();
    return 0;
}
