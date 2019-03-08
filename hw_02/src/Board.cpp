#include <utility>
#include <algorithm>
#include "Board.h"


Board::Board(int board_size, int win_ros_size): BOARD_SIZE(board_size), WIN_ROW_SIZE(win_ros_size) {
    filled_count = 0;
    cell_state_t* tmp = new cell_state_t[board_size * board_size];
    gameDesk = new cell_state_t*[board_size];
    for (int i = 0; i < board_size; ++i) {
        gameDesk[i] = (tmp + i * board_size);
    }
    init_desk();
    prev_x = 0;
    prev_y = 0;
    prev_player = CROSS;
}

Board::~Board() {
    delete[] gameDesk[0];
    delete[] gameDesk;
}

void Board::move(int x, int y, cell_state_t player) {
    gameDesk[x][y] = player;
    prev_x = x;
    prev_y = y;
    prev_player = player;
    filled_count++;
}

bool Board::canMove(int x, int y) {
    if(x >= BOARD_SIZE || y >= BOARD_SIZE || x < 0 || y < 0)
        return false;
    return gameDesk[x][y] == EMPTY;
}

void Board::init_desk() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            gameDesk[i][j] = EMPTY;
        }
    }
}

game_state_t Board::isWin() {

    cell_state_t cell = prev_player;
    std :: pair<int, int> directions[4];

    directions[0] = std::make_pair(0, 1);
    directions[1] = std::make_pair(1, 0);
    directions[2] = std::make_pair(1, 1);
    directions[3] = std::make_pair(1, -1);

    int total_count = -1;
    for (int i = 0; i < 4; ++i) {
        int forward = countInRow(directions[i].first, directions[i].second, cell);
        int backward = countInRow(-directions[i].first, -directions[i].second, cell);
        total_count = std::max(total_count, forward + backward - 1);
    }

    if (total_count >= WIN_ROW_SIZE)
        return (cell == CROSS) ? CROSS_WIN : ZERO_WIN;

    if (filled_count == BOARD_SIZE * BOARD_SIZE)
        return DRAW;

    return GAME;
}

int Board::countInRow(int dx, int dy, cell_state_t cellState) {

    int curr_count = 0;
    int x = prev_x;
    int y = prev_y;

    while(x < BOARD_SIZE && y < BOARD_SIZE && (x >= 0 && y >= 0) && curr_count < WIN_ROW_SIZE) {
        if (gameDesk[x][y] == cellState) {
            x += dx;
            y += dy;
            curr_count++;
        } else break;
    }

    return curr_count;
}

