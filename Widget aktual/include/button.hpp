#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "window.hpp"

using namespace std;

class Button : public Widget{
protected:
    string _title;
    string _ID;
    bool _clickable;
public:
    Button(Window * parent, int x, int y, int sx, int sy, string s, string az);
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void action() const;
    virtual string getValue() const;
    void set_clickable(bool mire);
};

#endif // BUTTON_HPP_INCLUDED
