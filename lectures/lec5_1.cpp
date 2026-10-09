/*
   C++

   auto для переменных, которые мы пока не знаем какого типа будут

namespace foo{
    const int x = 5;
    void t() {}
    namespace bar {
        floar b = 2.2;
    }
}
ПРОСТРАНСТВО ИМЕН
можно использовать:
int main() {
    const int y = foo::x;
    y;
    foo::t();
    foo::bar:b
}

ССЫЛКИ (похоже на указатель, но не является им)
swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

INCLUDE в C++
#include <iostream>
#include <stdint>

void print(const std::string &s){
    std::count << s << std::endl;
}

Ссылка - не полная замена указателей

RANGE FOR
for (объявление переменной : выражение) {
    // тело цикла
}

УПРАВЛЕНИЕ ПАМЯТЬЮ
int* p = new int;
int* q = new int(100);
int* r = new int();
int* s = new int{7}

delete p;
delete q;
delete r;
delete s;

выделение памяти для массивов
int* bar = new int[5]{1, 2, 3, 4, 5};
delete[] bar

выделенте памяти в уже выделенной памяти
char* buffer = new char[1024]
int* pi = new(buffer)
float* pf = new(buffer + sizeof(int)) float(3.14f);
в buffer дополнительно выделяем pi и pf

ОШИБКИ ВЫДЕЛЕНИЯ ПАМЯТИ (исключение)
try {
    while (true) {
        new int(1000000000000000l); //здесь должна быть ошибка, слищком большой объем
    }
} catch (const std::bad_alloc& e) {
    std::cout << e.what() << '\n';
}

nullptr
while (true) {
    new int(1000000000000000l); //здесь должна быть ошибка, слищком большой объем
    if (p == nullptr) {
    std::cout << "Allocarion returned\n";
}

АРГУМЕНТЫ ФУНКЦИЙ ПО УМОЛЧАНИЮ

ПЕРЕГРУЗКА ФУНКЦИЙ
создание одинаковых названий функций с разными агрументами
int add(int a, int b) {
    return a + b;
}

double add(float a, float b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << "\n" // вызов версии int
    srd::cout << add(2.5, 3.7) << "\n" // вызов версии double
}

ограничения на перегрузку функций
1. нельзя создавать новые операторы
2. нельзя переопределять операторы для встроенных типов
3. нельзя менять число аргументов, приоритет и ассоциативность
4. нельзя использовать аргументы по умолчанию

ПОТОКОВЫЙ ВВОД-ВЫВОД

std::cout << std::fixed << std::setprecision(2) << std::numbers::pi << "\n"; // 3.14
std::cout << std::dec << 255 << "\n" // 255

ПОТОКОВЫЙ ВВОД С ПОМОЩЬЮ <<
int main() {
    int age;
    std::string name;
    std::cout << "Введите имя"
    std::getline(std::cin, fullName); // читает строку до \n
}

ПРИВЕДЕНИЕ ТИПОВ
int i = (int)d
int i = static_cast<int>(d) // в основном используем статичсекое

ШАБЛОНЫ
средство обобщенного программирования,
позволяющее описывать функции, классы и переменные без привязки к типам данных или значениям

пример:
template <typename T>
void swap(&T a, T& b) {
    T temp = a;
    a = b
    b = temp
}

// Где-то в коде
int x = 1, y = 2;
swap(x, y)

double q = 1.5, q = 3.7;
swap(p, q);

cppreference.com
*/