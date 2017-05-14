#include "window.hpp"
#include "graphics.hpp"
#include <iostream>
#include <fstream>

using namespace genv;

Window::Window(int x, int y)
{
    XX=x;
    YY=y;
}

void Window::set_run(bool run)
{
    _run=run;
}

void Window::event_loop()
{
    ofstream kifele("adatok.txt");
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
    kifele.close();
}

void Window::push_item(Widget * w)
{
    widgets.push_back(w);
}

void Window::action(string ID) {}

//File-ba írás
/* if(ev.type==ev_key && ev.keycode==key_f1)
 {
     for (size_t i=0; i<widgets.size(); i++)
     {

         kifele<<i+1<<". widget erteke: " << dynamic_cast(widgets[i])->getValue()<<"\n";
     }
     kifele<<"--------------\n";
     cout<<"Successful save"<<'\n';
 }*/
