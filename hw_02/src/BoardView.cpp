//
// Created by ivan on 06.12.18.
//

#include <iostream>
#include <cstdio>
#include "BoardView.h"

BoardView::BoardView(bool silence, Board &board1) : board(board1) {
    this->silence = silence;
}

void BoardView::showBoard() {
    for (int i = 0; i < board.get_board_size(); ++i) {
        for (int j = 0; j < board.get_board_size(); ++j) {
            char out = '.';
            if (board.get_cell(i, j) == CROSS) {
                out = 'X';
            } else if (board.get_cell(i, j) == ZERO) {
                out = 'O';
            }
            printf("%c", out);
        }
        printf("\n");
    }
}

void BoardView::doGameCycle() {
    bool isPlayerX = false;
    bool isBadMove = false;
    bool exit = false;
    while (board.isWin() == GAME) {

        if (!isBadMove && !silence)
            showBoard();

        if (isPlayerX)
            printf("X move: ");
        else
            printf("O move: ");

        int x, y;
        std::cin >> x >> y;
        if (x == -1 && y == -1) {
            exit = true;
            break;
        }

        if (!board.canMove(x, y)) {
            printf("Bad move!\n");
            isBadMove = true;
        } else {
            board.move(x, y, (isPlayerX) ? CROSS : ZERO);
            printf("\n");
            isPlayerX = !isPlayerX;
            isBadMove = false;
        }
    }
    if (!exit) {
        showBoard();
        if (board.isWin() == CROSS_WIN) {
            printf("X wins!\n");
        } else if (board.isWin() == ZERO_WIN) {
            printf("O wins!\n");
        } else {
            printf("Draw.\n");
        }
    }
}









