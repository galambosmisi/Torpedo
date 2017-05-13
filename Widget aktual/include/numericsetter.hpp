#ifndef NUMERICSETTER_HPP_INCLUDED
#define NUMERICSETTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

using namespace std;

class NumericSetter : public Widget
{
protected:
    int _min, _max, num;
    double box_size;
public:
    NumericSetter(Window * parent, int x, int y, int sx, int sy, int mini, int maxi );
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual string getValue() const ;
};

#endif // NUMERICSETTER_HPP_INCLUDED
