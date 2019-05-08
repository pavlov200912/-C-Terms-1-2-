//
// Created by ivan on 21.04.19.
//

#ifndef HW_03_AUTOTEST_H
#define HW_03_AUTOTEST_H


#include <cstdio>
#define DO_CHECK(expr) check(expr, __FUNCTION__, __FILE__, __LINE__)

class Test {
public:
    static void check(bool expr, const char *func, const char  *filename, size_t lineNum);
    static void showFinalResult();
    virtual void runAllTests() = 0;

protected:
    static int failedNum;
    static int totalNum;
};


#endif //HW_03_AUTOTEST_H
