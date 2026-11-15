/*
ЛЕКЦИЯ 8

!!! ЗАМЫКАНИЯ В C++ !!!
ЗАМЫКАНИЕ (closure) - безымянный объект-функция, который захватывает переменные из окружающей области видимости.

АНОНИМАНАЯ ФУНКЦИЯ - функция, задаваемая без имени, обычно через лямбда-абстракцию.
Например, в математической нотации: lx.x + C или x |-> x + C.
Практический вариант определения - функциия, определенная непосредственно в месте использования.

Аналог на Python: лямбда-функция

ПРИМЕР НА PYTHON
С = 10
xs = list(map(lambda x: x + C, [1, 2, 3]))
# xs = [11, 12, 13]

ПРИМЕР НА C++
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
    int C = 10;
    std::vector<int> v{1, 2, 3};
    std::vector<int> result;

    std::transform(v.begin(), v.end(), std::back_inserter(result),
                   [C](int x) {return x + C; });
    // result = {11, 12, 13}
}

ЛЕКСИЧЕСКОЕ ЗАМЫКАНИЕ
Если функция определена внутри другой функции, то она является лексическим замыкание по отношению к ней.

ПРИМЕР ЛЯМБДА-ФУНКЦИИ C++

int x = 10;
auto lambda = [x](int y) { return x + y; };

class Closure {
    int x;
public:
    Closure(int x_) : x(x_) {}
    int operator()(int y) const { return x + y; }
};
Closure lambda(x);

СПОСОБЫ ЗАХВАТА ПЕРЕМЕННЫХ
[] - ничего не захватывать
[x] - захватить переменную
[&x] - по ссылке
[x, &y] - x - по значению, y - по ссылке
[=] - захватить все используемые автоматические переменные по ссылке
[this] - захватить указатель this
[&, x] - по умолчанию - по ссылке, но x - по значению
[=, &x] - по умолчанию - по значению, но x - по ссылке

STD::FUNCTION
Универсальная обертка для вызываемых объектов

#include <functional>

std::function<int(int)> f; // функция, принимает int, возвращает int
std::function<void()> action; // процедура без параметров

ПРИМЕР 1
#include <iostream>

int main() {
    int a = 10;
    int b = 10;

    auto byValue = [a]() { return a; }
    auto byRef   = [&b}() { return b; }

    a = 99;
    b = 99;

    std::cout << byValue() << '\n'; // 10 - копия
    std::cout << byRef() << '\n'; // 99 - улавливает актуальное значение, так как по ссылке

ПРИМЕР 3

std::function<bool(int)> makeIsBig(int limit) {
    return [limit](int x) { result x >= limit; };
}

int main() {
auto isBig = makeIsBig(99)
std::cout << makeIsBig(150) // true
}

КАРИРОВАНИЕ ???

АНАЛОГ MAP - STD::STRANSFORM

ЗАГОЛОВОЧНЫЙ ФАЙЛ <ALGORITHM>
Набор готовых обобщенных операций над диапазонами [first, last).
Главная идея: вместо ручных циклов for мы называем что хотим сделать, а не как перебирать элементы.

"<algorithm> + <functional> + лямбда-выражения дает самый короткий и выразительный код"

std::all_of    : все элементы удовлетворяют условию
std::any_of    : хотя бы один удовлетворяет
std::none of   : ни один не удовлетворяет
std::sort      : сортировка
std::transform : отображает каждый элемент
std::remove_if : "сдвигает" ненужные элементы
std::iota      : заполняет диапазон

ПРИМЕР ПРОВЕРКИ
std::vector<int> v{2, 4, 6, 8};

bool all_even = std::all_of (v.begin(), v.end(), [](int x) { return x % 2 == 0; });

СВЕРТКА (FOLD)
операция, которая "сворачивает" последовательноссть элементов в одно итоговое значение путем
последовательного применения бинарной функции.

ИДИОМА ERASE-REMOVE: REMOVE_IF
std::remove_if не удаляет элементы из контейнера.

*/