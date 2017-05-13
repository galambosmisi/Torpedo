#ifndef EXAMPLECHECKBOX_HPP_INCLUDED
#define EXAMPLECHECKBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class CheckBox : public Widget {
protected:
    bool _checked;
public:
    CheckBox(Window * parent, int x, int y, int sx, int sy);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual bool is_checked() const ;
    virtual string getValue() const;
};


#endif // EXAMPLECHECKBOX_HPP_INCLUDED
