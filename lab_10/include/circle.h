#pragma once

#include "figure.h"

class Circle : public Figure {
  public:
    Circle(int id, int x, int y, int radius, const char* label);
    virtual ~Circle();

    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    virtual void zoom(int factor);

   private:
    int radius;
    char* label;
};
