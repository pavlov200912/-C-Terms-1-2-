
#include <rectangle.h>
#include <cstdio>
#include <cstdlib>

#include "rectangle.h"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    this->width = width;
    this->height = height;
}

void Rectangle::zoom(int factor) {
    height *= factor;
    width *= factor;
}

bool Rectangle::is_inside(int x, int y) const {
    int dx = abs(x - this->x);
    int dy = abs(y - this->y);
    return (2 * dx <= width && 2 * dy <= height);
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n",
            id, x, y, width, height);
}

