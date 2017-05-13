#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

using namespace std;

class Map : public Widget
{
protected:
    int box_size;
    vector<vector<bool> shots;
public:
    NumericSetter(Window * parent, int x, int y, int sx, int sy, int mini, int maxi );
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual string getValue() const ;
};


#endif // MAP_H_INCLUDED
