#include "graphics.hpp"
#include "widgets.hpp"
#include "window.hpp"
#include "button.hpp"
#include "examplecheckbox.hpp"
#include "statictextbox.hpp"
#include "dynamictextbox.hpp"
#include "numericsetter.hpp"
#include "dropdownmenu.hpp"
#include "player.hpp"
#include "map.hpp"
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
    vector<Ship> s;
    Map * m;
    Button * b1;
    Button * b2;
    DynamicTextBox * dtx;
    StaticTextBox * stx1;
    StaticTextBox * stx2;

    setUpMenu(int x, int y, string p_id) : Window(x,y)
    {
        m = new Map(this, 450,90,30, "setUp_map");
       b1 = new Button(this, 565,420,120,30,"Kész","player_done");
       b2 = new Button(this, 175,420,120,30,"Tiszta lap","storno");
      dtx = new DynamicTextBox(this, 395,10,150,30,p_id,true);
     stx1 = new StaticTextBox(this, 295,10,30,"Játkos neve:", false);
     stx2 = new StaticTextBox(this, 10,90,30,"Helyezd el a hajókat", false);
    }

    void action(string _ID)
    {
        if(_ID=="player_done")
        {
            set_run(false);
        }
    }

};

class Torpedo : public Window
{
protected:
    Player * p1;
    Player * p2;
    string active_player="p1";
    bool shot=false;


public:

     Torpedo(int x, int y, vector<Ship> s1, vector<Ship> s2, string player_id1, string player_id2) : Window(x, y)
    {
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
