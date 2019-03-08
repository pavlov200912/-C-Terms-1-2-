#include <iostream>
#include <cstring>
#include "Board.h"
#include "BoardView.h"

int main(int argc, char* argv[]) {
    bool silence = (argc > 1) && (!strcmp("silent", argv[1]));
    Board b;
    BoardView game(silence, b);
    game.doGameCycle();
    return 0;
}
