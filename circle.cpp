#include <gl/gl.h>
#include <cmath>
#include "circle.h"


Circle::Circle() {}

Circle::Circle(float _x, float _y, float _r, Color& _col) : x(_x), y(_y), r(_r), col(_col) {}

Circle::~Circle() {}
void Circle::draw()
{
    //можна на перед визначити точки і через масив індексів вивести на екран круг
    int circle_point = 24;
    float angle;

    glBegin(GL_TRIANGLE_FAN);

        glColor3f(col.r, col.g, col.b);
        for(int i = 0; i < circle_point; i++)
        {
            angle = 2 * M_PI * i / circle_point;
            glVertex2f(cos(angle) * r + x, sin(angle) * r + y);
        }

    glEnd();
}

