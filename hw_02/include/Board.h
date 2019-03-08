//
// Created by ivan on 06.12.18.
//

#ifndef HW_02_BOARD_H
#define HW_02_BOARD_H

enum game_state_t{
    ZERO_WIN,
    CROSS_WIN,
    DRAW,
    GAME,
};

enum cell_state_t{
    ZERO = -1,
    EMPTY,
    CROSS
};

class Board {
public:
    Board(int BOARD_SIZE = 10, int WIN_ROW_SIZE = 5);
    ~Board();

    cell_state_t get_cell(int x, int y) {return gameDesk[x][y];}
    int get_board_size() {return BOARD_SIZE;}
    void init_desk();
    void move(int x, int y, cell_state_t player); // сделать ход
    bool canMove(int x, int y); // корректен ли ход
    game_state_t isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    int countInRow(int dx, int dy, cell_state_t cellState);
private:

    int BOARD_SIZE;
    int WIN_ROW_SIZE;

    cell_state_t** gameDesk;

    int prev_x;
    int prev_y;
    cell_state_t prev_player;

    int filled_count;
};


#endif //HW_02_BOARD_H
