// 4, 5, 6 задачи и еще одно из 1, 2, 3.
#include <iostream>

int main() {
    const auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";
    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }
    return 0;
}

// Для написания BIg Int:
// BigInt result(1);
// for (int i = 1; i <= 100500; i++) {
//     result = result(*i);

//
// 5 номер в дз лучше разделить на три файла, например:
// main.cpp
// person.cpp
// person.h

// в 6 лучше избежать квадратных корней
