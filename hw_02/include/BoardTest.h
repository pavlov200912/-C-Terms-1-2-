#ifndef HW_02_BOARDTEST_H
#define HW_02_BOARDTEST_H


#include "Board.h"
#include "Test.h"

class BoardTest : Test{
public:
    void testIsWin1();
    void testIsWin2();
    void testIsWin3();
    void testMove1();
    void testMove2();
    void testMove3();
    void testCanMove1();
    void testCanMove2();
    void testCanMove3();
    void testCanMove4();
    void testCanMove5();
    void extraTest();
    virtual void runAllTests() {
        testIsWin1();
        testIsWin2();
        testIsWin3();
        testMove1();
        testMove2();
        testMove3();
        testCanMove1();
        testCanMove2();
        testCanMove3();
        testCanMove4();
        testCanMove5();
        extraTest();
    }
};


#endif //HW_02_BOARDTEST_H
