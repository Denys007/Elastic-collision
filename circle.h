#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "Color.h"

class Circle
{
public:
    Circle();
    Circle(float _x, float _y, float _r, Color& _col);
    ~Circle();

    void draw();

    float x;
    float y;
    float r;
    Color col;
};

#endif // CIRCLE_H_INCLUDED
