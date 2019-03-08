#pragma once

class Figure {
  public:
    Figure(int id = 0, int x = 0, int y = 0);
    virtual ~Figure(){};

    int get_id(){return id;}
    virtual void print() const = 0;
    virtual bool is_inside(int x, int y) const = 0;
    virtual void zoom(int factor) = 0;
    void move(int new_x, int new_y);

  protected:
    int id;
    int x;
    int y;
};
