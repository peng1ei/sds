#include <iostream>
#include <vector>

#include "vector/sds_vector.hpp"

void TestStdVectorReverse() {
    std::vector<int>::size_type sz;

  std::vector<int> foo;
  sz = foo.capacity();

    std::cout << sz << std::endl;

  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  std::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

void TestSdsVectorReverse() {
    size_t sz;

  sds::Vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  sds::Vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

class A {
    public:
        ~A() {
            std::cout << "~A()" << std::endl;
        }

        void print() {
            std::cout << "print()" << std::endl;
        }
};

int main() {
    //TestStdVectorReverse(); 
    //std::cout << "----------------------------" << std::endl;
    //TestSdsVectorReverse();
    //sds::Vector<A> vec;
    std::vector<A> vec;
    vec.push_back(A());

    std::cout << vec.capacity() << std::endl;

    vec.pop_back();
    //vec.erase(vec.end()-1);
    std::cout << vec.capacity() << std::endl;

    auto elem = vec[0];
    elem.print();

    return 0;
}