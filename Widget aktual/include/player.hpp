#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "graphics.hpp"
#include "statictextbox.hpp"
#include "button.hpp"
#include "map.hpp"

class Player : public Window
{
    string player_id;
    string player_name;
    Window * _parent;
    int XX,YY,life;
    StaticTextBox * stx1;
    StaticTextBox * stx2;
    StaticTextBox * stx3;
    StaticTextBox * stx4;
    StaticTextBox * stx5;
    Button * b;
public:

    Player(Window * parent, string p_id, string p_name, int x, int y);
    string get_ID();
    string get_name();
    void action(string _ID);
    void event_loop();
    int get_life() const;
};

#endif // PLAYER_HPP_INCLUDED
