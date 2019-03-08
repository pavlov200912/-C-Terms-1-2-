#pragma once

#include "figure.h"

class Rectangle: public Figure {
  public:
    Rectangle(int id, int x, int y, int width, int height);

    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    virtual void zoom(int factor);

  private:
    int width;
    int height;
};
