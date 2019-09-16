#include <list>
#include <iostream>
#include <vector>

void StdListRun() {
    std::list<int> empty_list;
    std::cout << "empty list." << empty_list.size() << std::endl;
    std::cout << "max size: " << empty_list.max_size() << std::endl;

    std::list<int> fill_list(6);
    std::cout << "fill list: " << fill_list.size() << " first: " << fill_list.front() << std::endl;
    std::cout << "max size: " << fill_list.max_size() << std::endl;

    std::list<int> fill_val_list(6, 100);
    std::cout << "fill val list: " << fill_list.size() << " first: " << fill_val_list.front() << std::endl;

    std::vector<int> vec{ 1, 2, 3, 4, 5, 6 };
    std::list<int> range_list(vec.begin(), vec.end());
    std::cout << "range list: " << range_list.size() << " first: " << range_list.front() << std::endl;
    std::cout << "max size: " << range_list.max_size() << std::endl;
    for (auto e : range_list)  {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    int arr[6]{0, 1, 2, 3, 4, 5};
    std::list<int> range_arr_list(arr, arr + 4);
    for (auto e : range_arr_list) {
        std::cout << e << " ";
    }

    std::cout << std::endl;

    int a = 0;
    std::list<int> init_list = {1, 2, 3, 4, 5, a, 7, 8};
    for (auto e : init_list) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    std::list<int> copy_list(init_list);
    for (auto e : copy_list) {
        std::cout << e << " ";
    }

    if (copy_list.empty()) {
        std::cout << "copy is empty" << std::endl;
    } else {
        std::cout << "copy is't empty" << std::endl;
    }

    std::cout << "first: " << copy_list.front() << std::endl;
    std::cout << "back: " << copy_list.back() << std::endl;

    copy_list.push_front(888);
    std::cout << "first: " << copy_list.front() << std::endl;

    copy_list.push_back(999);
    std::cout << "back: " << copy_list.back() << std::endl;

    copy_list.pop_front();
    copy_list.pop_back();

    std::cout << "first: " << copy_list.front() << std::endl;
    std::cout << "back: " << copy_list.back() << std::endl;

    std::cout << "size: " << copy_list.size() << std::endl;
    copy_list.erase(copy_list.begin());
    std::cout << "size: " << copy_list.size() << std::endl;

    //copy_list.clear();
    //std::cout << "size: " << copy_list.size() << std::endl;
    

      std::list<int> mylist;

        for (int i=1; i<10; ++i) mylist.push_back(i);

        mylist.reverse();

        std::cout << "mylist contains:";
        for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
        std::cout << ' ' << *it;

        std::cout << '\n';

}