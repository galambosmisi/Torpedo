#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED


#include "widgets.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Widget;

class Window {
protected:
    vector<Widget*> widgets;
    bool _run=true;
    int focus = -1;
public:
    int XX, YY;
    Window(int x, int y);
    virtual void event_loop();
    void push_item(Widget * w);
    void set_focus(int i);
    void set_run(bool run);
    virtual void action(string ID);
};

#endif // WINDOW_HPP_INCLUDED
