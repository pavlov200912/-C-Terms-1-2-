#ifndef HW_02_BOARDVIEW_H
#define HW_02_BOARDVIEW_H

#include "Board.h"

class BoardView {
public:
    BoardView(bool silence, Board &board1);
    void showBoard(); //вывод доски на экран
    void doGameCycle(); //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
private:
    Board& board;
    bool silence;
};

#endif //HW_02_BOARDVIEW_H
