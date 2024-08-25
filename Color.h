#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

class Color
{
public:
    Color();
    Color(short _r, short _g, short _b);
    ~Color();

    short r;
    short g;
    short b;
};

#endif // COLOR_H_INCLUDED
