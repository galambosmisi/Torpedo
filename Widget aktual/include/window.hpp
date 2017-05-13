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
    int XX, YY;
    bool _run=true;
public:
    Window(int x, int y);
    virtual void event_loop();
    void push_item(Widget * w);
    void set_run(bool run);
    virtual void action(string ID);
};

#endif // WINDOW_HPP_INCLUDED
