#ifndef DYNAMICTXTBOX_H_INCLUDED
#define DYNAMICTXTBOX_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "statictextbox.hpp"

using namespace std;

class DynamicTextBox : public StaticTextBox {
protected:
    string _start;
public:
    DynamicTextBox(Window * _parent, int x, int y, int sx, int sy, string S, bool asd);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual void set_text(string s);
    virtual string getValue() const;
};

#endif // DYNAMICTXTBOX_H_INCLUDED
