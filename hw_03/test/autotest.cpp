//
// Created by ivan on 21.04.19.
//

#include "autotest.h"

int Test::failedNum = 0;
int Test::totalNum = 0 ;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        printf("test failed: %s in %s:%zu\n", func, filename, lineNum);
        failedNum++;
    }
}

void Test::showFinalResult() {
    failedNum == 0 ? printf("All tests passed.\n") : printf("Failed %d of %d tests.\n", failedNum, totalNum);
}