#ifndef DROPDOWNMENU_HPP_INCLUDED
#define DROPDOWNMENU_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

using namespace std;

class DropDownMenu : public Widget
{
protected:
    vector <string> items;
    double box_size, slider_size;
    int actual, max_item, first_item;
    bool isDown=false;
    bool click = false;

public:
    DropDownMenu(Window * parent,int x, int y, int sx, int sy, int max_i, vector <string>& s);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void add_answer(string s);
    virtual void delet_actual_answer();
    virtual void set_ex_size();
    virtual string getValue() const;
};

#endif // DROPDOWNMENU_HPP_INCLUDED
