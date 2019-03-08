
#include <circle.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "circle.h"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y){
    this->radius = radius;

    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n",
            id, x, y, radius, label);
}

bool Circle::is_inside(int x, int y) const {
    int x0 = (x - this->x);
    int y0 = (y - this->y);
    return x0 * x0  + y0 * y0 <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}

Circle::~Circle(){
    delete[] label;
}
