#ifndef SDS_LEETCODE_TEST_H
#define SDS_LEETCODE_TEST_H
#include "include/core.h"

#include "array/no_0001.hpp"

void LeetCodeUsage() {
    std::cout << "Usage: $ ./a.out 0001\n" << std::endl;
    std::cout << "NO.0001 两数之和[https://leetcode-cn.com/problems/two-sum]" << std::endl; 


    std::cout << std::endl;
}

void LeetCode(int argc, char *argv[]) {
    if (argc < 2) {
        LeetCodeUsage();
        return;
    }

    int number = atoi(argv[1]);
    assert(number >= 1);

    switch (number)
    {
    case 0001:
        Solution_0001().run();
        break;
    default:
        std::cout << "Please wait for the update with NO." << argv[1] << std::endl;
        break;
    }
}

#endif // SDS_LEETCODE_TEST_H