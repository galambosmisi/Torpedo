#ifndef STATICTEXTBOX_HPP_INCLUDED
#define STATICTEXTBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

using namespace std;

class StaticTextBox : public Widget {
protected:
    string _s;
    bool _box;
public:
    StaticTextBox(Window * parent, int x, int y, int sx, int sy, string S, bool is_box);
    StaticTextBox(Window * parent, int x, int y, int sy, string S, bool is_box);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void set_text(string s);
    virtual string getValue() const;
};

#endif // STATICTEXTBOX_HPP_INCLUDED
