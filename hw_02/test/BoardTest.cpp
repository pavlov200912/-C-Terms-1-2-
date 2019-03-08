#include "BoardTest.h"

void BoardTest::testIsWin1() {
    Board b;
    b.move(5, 5, ZERO);
    b.move(4, 3, CROSS);
    b.move(4, 5, ZERO);
    b.move(6, 5, CROSS);
    b.move(3, 5, ZERO);
    b.move(6, 3, CROSS);
    b.move(2, 5, ZERO);
    b.move(1, 3, CROSS);
    b.move(1, 5, ZERO);
    DO_CHECK(b.isWin() == ZERO_WIN);
}

void BoardTest::testIsWin2() {
    Board b;
    /*
    *    OOXXOOXXOO
    *    XXOOXXOOXX
    *    OOXXOOXXOO
    *    XXOOXXOOXX
    *    OOXXOOXXOO
    *    XXOOXXOOXX
    *    OOXXOOXXOO
    *    XXOOXXOOXX
    *    OOXXOOXXOO
    *    XXOOXXOOXX
    */
    cell_state_t x = CROSS;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; j += 2) {
            b.move(i, j, x);
            b.move(i, j + 1, x);
            x = (x == CROSS) ? ZERO : CROSS;
        }
    }
    DO_CHECK(b.isWin() == DRAW);
}

void BoardTest::testIsWin3() {
    Board b;
    b.move(5, 5, ZERO);
    b.move(4, 3, CROSS);
    b.move(4, 5, ZERO);
    b.move(6, 5, CROSS);
    b.move(3, 5, ZERO);
    b.move(6, 3, CROSS);
    b.move(2, 5, ZERO);
    b.move(1, 3, CROSS);
    DO_CHECK(b.isWin() == GAME);
}

void BoardTest::testMove1() {
    Board b;
    b.move(0, 0, CROSS);
    DO_CHECK(b.get_cell(0, 0) == CROSS);
}

void BoardTest::testMove2() {
    Board b;
    b.move(6, 6, ZERO);
    DO_CHECK(b.get_cell(6, 6) == ZERO);
}

void BoardTest::testMove3() {
    Board b;
    b.move(5, 5, CROSS);
    DO_CHECK(b.get_cell(1, 1) == EMPTY);
}

void BoardTest::testCanMove1() {
    Board b;
    b.move(0, 0, CROSS);
    DO_CHECK(!b.canMove(0, 0));
}

void BoardTest::testCanMove2() {
    Board b;
    b.move(9, 9, ZERO);
    DO_CHECK(!b.canMove(9, 9));
}

void BoardTest::testCanMove3() {
    Board b;
    b.move(5, 5, ZERO);
    DO_CHECK(b.canMove(1, 1));
}

void BoardTest::testCanMove4() {
    Board b;
    DO_CHECK(!b.canMove(-1, 10));
}

void BoardTest::testCanMove5() {
    Board b;
    DO_CHECK(!b.canMove(5, 10));
}

void BoardTest::extraTest() {
    Board b(3, 3);
    b.move(0, 0, ZERO);
    b.move(1, 0, CROSS);
    b.move(1, 1, ZERO);
    b.move(0, 1, CROSS);
    b.move(2, 2, ZERO);
    DO_CHECK(b.isWin() == ZERO_WIN);
}
