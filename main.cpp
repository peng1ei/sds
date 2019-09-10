#include <iostream>
#include <vector>

#include "vector/sds_vector.hpp"

int main() {
    std::cout << "hello world" << std::endl;
    std::vector<int> vec{ 0, 1, 2, 3, 4, 5 };
    auto iter = vec.begin();
    std::cout << *iter << std::endl;

    *(iter + 5) = 99;
    for (; iter != vec.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << iter[2] << std::endl;

    std::cout << *iter << std::endl;
    std::cout << iter[5] << std::endl;
    std::cout << *iter << std::endl;

    sds::Vector<int> my_vec{ 1, 2, 3, 4, 5, 6 };
    my_vec.print();
    auto &my_first = my_vec.front();
    std::cout << my_first << std::endl;

    auto my_iter = my_vec.begin();
    *my_iter = 100;
    *(my_iter + 5) = 88;
    for (; my_iter != my_vec.end(); ++my_iter) {
        std::cout << *my_iter << " ";
    }
    std::cout << std::endl;

    return 0;
}