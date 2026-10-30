/*
---------

ЛЕКЦИЯ 4


!!! ШАБЛОНЫ В C++ !!!
средство обобщенного программирования, которое позволяет писать код, параметризованный типами,
значениями или другими шаблонами.

ШАБЛОНЫ ФУНКЦИИ

template <typename T> // шаблон
void my_swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

int main() {
    int x = 1, y = 2;
    my_swap(x, y);
    std::cout << x << " " << y << "\n"; // 2 1

    std::string s1 = "foo", s2 = "bar";
    my_swap(s1, s2);
    std::cout << s1 << " " << s2 << "\n" // bar foo

Работает для тех типов значений, которые получает на вход (функция перегружена для двух типов)


ШАБЛОНЫ КЛАССОВ: ОДНОСВЯЗНЫЙ СПИСОК

template <typename T> // шаблон
class List {
private:
    struct Node {
        T value
        Node* next
        Node(const T& v, Node* n): value(v), next(n) {}
    };
    Node* head_;
public:
    List() : head_(nullptr) {}
    List(const List&) = delete;
    List& operator = (const List&) = delete

    ~List() {
    while (head_ != nullptr) {
        drop();
    }
}

// Добавление элемента в голлову списка
void cons(const T& value) {
    head_ = new Node(value, head_);
}

// Получение головы: указатель на первый элемент или nullptr
T* head() {
    if (head_ == nullptr) { return nullptr; }
    return &head_ -> value;
}

// Удаление элемента из головы: если список пуст - ничего не делает
void drop() {
    if (head_ != nullptr) {
        Node* old = head_;
        head_ = head_ -> next;
        delete old;
    }
}

int main() {
    List<int>list;

    list.cons(30);
    list.cons(20);
    list.cons(10);

    if (int* p = list.head()) {
        std::cout << *p << "\n"; // 10
    }
    list.drop(); // удалили 10

    if (int* p = list.head()) {
        std::cout << *p << "\n"; // 20
    }
    list.drop(); // удалили 20


ШАБЛОНЫ С КОНСТАНТАМИ

template <typename T, std::size_t N> // шаблон с его параметрами
class Array {
private:
    T data_[N];
    std::size_t size_ = 0;
public:
    T& operator[](std::size_t index) {
        return data_[index];
    }
    const T& operator[](std::size_t index) const {
        return data_[index];
    }
    std::size_t capacity() const {
        return N; // N известен на этапе компиляции
    }
}

int main() {
    Array<int, 5> a; // Получим эквивалент int a[5];
    Array<double, 2> b; // Получим эквивалент double b[2];
}


ВАРИАДИЧЕСКИЕ ШАБЛОНЫ

template <typename... Ts>
void print(const Ts&..., args) {
    // ((std::cout << args << ' ') , ...) = (std::cout << args << ' '),
    // (std::cout << args << ' '), (std::cout << args << ' '), (std::cout << args << ' ')
    ((std::cout << args << ' ') , ...); // что-то вроде цикла: выводим все переменные
    std::cout << '\n';
}

int main() {
    print(1, 2.5, "hello", 'x');
    // 1 2.5 hello x
}

ОТЛАДКА ШАБЛОНОВ

template<> void print<<int, double, char[6], char>> (
    const int &args, const double &args, const char &args[6], const char &args) {
    (std::cout << args << ' '), (std::cout << args << ' '), (std::cout << args << ' '),
    (std::cout << args << ' ');
    std::cout << '\n';
}


!!! СТАНДАРТНАЯ БИБЛИОТЕКА ЯЗЫКА C++ !!!

КОНТЕЙНЕРЫ В STL

std::vector динамический массив         std::vector<int> vec;
std::map    словарь                     std::map<std::string, int> map;
std::set    упорядоченное множество     std::set<int> set;
std::list   двусвязный список           std::list<double> lst;
std::stack  стек

ВЕКТОР
динамический массив(расширяемая последовательность элементов), хранящийся в непрерывной области памяти

ВЕКТОР: ПРИМЕР

#include <vector>

using namespace std; // позволяет вместо std::vector писать vector (std::v -> v)

int main() {
    vector<int> v; // пустой вектор

    // --- Добавление ---
    v.push_back(10); // добавление в конец
    v.push_back(20); // добавление в конец
    v.emplace_back(30); // похож на push_back
    v.insert(v.begin() + 1, 99); // вставить 99 на позицию 1 -> {10, 99, 20, 30}

    // --- Размер и емкость ---
    cout << v.size() << " " << v.capacity() << " " << v.empty() << "\n";
    v.reserve(50);           // зарезервировать память (без реллокаций при росте)

    // --- Доступ ---
    cout << v[0] << " " << v.at(1) << " " << v.front() << " " << v.back() << "\n"; // v[0] ~ v.at(1)
    int* raw = v.data();     // указатель на непрерывный буфер

    // --- Обход (range-based for) ---
    for (const &auto x: v) cout << x << " ";
    cout << "\n";

    // --- Удаление ---
    v.pop_back();            // удалить последний
    v.erase(v.begin());      // удалить первый

    // идиома erase-remove
    v.erase(remove(v.begin(), v.end(), 99), v.end());
    cout << "\n";

    // --- Сортировка / поиск (<algorithm>) ---
    sort(v.begin(), v.end());
    if (find(v.begin(), v.end(), 20) != v.end()) cout << "найдено\n";

    // --- Очистка ---
    v.clear();               // size = 0, capacity сохраняется
    v.shrink_to_fit();       // освободить лишнюю память, которая не заполнена ничем

    return 0;
}

--------

ЛЕКЦИЯ 5

Важнейшие методы

push_back / emplace_back // добавить в конец
pop_back                 // удалить с конца
operator[] / at          // доступ по индексу
front / back             // первый / последний
size / empty             // размер / пустота
reserve                  // зарезервировать память
insert / erase           // вставка / удаление
clear                    // удалить все элементы
data                     // указатель на буфер


ИТЕРАТОРЫ


Итератор - обобщенный указатель ...

ОБЫЧНЫЙ ИТЕРАТОР

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); i++) {
        *it *= 10;


Почему ++it, а не it++

++it // сначала перейдем к следующему, затем разыменовать
// не нужна копия, поэтому работает быстрее

it++ // разыменовывает, потом увеличивает

КОНТСАНТНЫЙ ИТЕРАТОР

for (std::vector<int>::const_iterator it = v.cbegin(); it != v.end(); ++it) {
    std::cout << "it" << " "; // только чтение
}

ОСНОВНОЕ ПРИМЕНЕНИЕ

std::sort(v.begin(), v.end());               // сортировка
auto it = std::find(v.begin(), v.end(), 30); // поиск
if (it != v.end()) ( / элемент найден / )

ЕСЛИ НАДО ОПРЕДЕЛИТЬ СВОЙ СОБСТВЕННЫЙ ИТЕРАТОР

template <typename T>
class ArrayIterator {
    T* ptr;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = &T;
    // using это как typedef в C

    explicit ArrayIterator(T* p) : ptr(p) {} // конструктор // Требование явного преобразования типов

    // Разыменование
    reference operator*() const {return *ptr;} // Указатель -> ссылка
    pointer operator -> () const {return ptr; }

    // Инкремент / декремент
    ArrayIterator& operator++() {ptr; return *this;}
    ...

    // Арифметика
    ArrayIterator& operator+=(difference_type n) { ptr += n; return *this; }
    ...

ПРИМЕНЕНИЕ
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    ArrayIterator<int> begin(arr);
    ArrayIterator<int> end(arr + 5);

    for (auto it = begin; it != end; ++it) {
        std::cout << "it << " "; // 10 20 30 40 50
    }
    std::cout << std.endl;
}

STD::MAP
контейнер словарей из элементов ключ-значение.

// Функция печатает словарь в формате [ключ] = значение

void print_map(std::string_view comment, const std::map<std::string, int>& m);
// string_view позволяет смотреть на часть строки без копирования

int main() {
    // Иници ализация map из трех пар. Внутри хранится (по порядку ключей):
    // CPU -> 10, GPU -> 15; RAM -> 20
    std::map<std::string, int> m({"CPU", 10}, {"GPU", 15}, {"RAM", 20});

    print_map(*1) Initial map: ", m);

    m["CPU"] = 25; // operator[] на СУЩЕСТВУЮЩЕМ ключе - присваивание (не вставка)
    m["SSD"] = 30; // operator[] на НЕсуществующем ключе - ВСТАВКА нового элемента
    // Теперь внутри: CPU = 25, GPU = 15, RAM = 20 (по алфавиту)
    print_map( ... )

    ...

void print_map( ... ) {
    std::cout << comment;

    for (const &auto [key, value] ; n) {
        std::cout << '[' << key << "] = " << value << "; ";
    std::cout << "\n";
}


STD::SET
упорядоченное множество уникальных элементов

STD::MULTISET и STD::MULTIMAP
тоже что и STD::SET, но можно несколько раз добавить один и тот же элемент и еще считает частоту.
частотный словарь
(например, сколько раз используется к-н слово)

STD::STRING
строка


!!! СЕМАНТИКА ПЕРЕМЕЩЕНИЯ В C++ !!!
механизм, который позволяет владение ресурсами (например. динамической памятью) от одного объекта
другому без копирования (которое требует затрат времени и памяти)

Идея: в отличие от копирование, которое дублирует данные, перемещение "забирает" из одного места
и пере дает в другое.

ОТКУДА ПРОБЛЕМА

int a = 10; // a - lvalue
int b = a + 5; // (a+5) -- rvalue (временный объект без адреса)
std::string s = "hi"; // s -- lvalue

// можно перемещать, если исходный объект больше не используем (он становится инвалидным)

v.push_back(std::move(s));

Когда использовать семантику перемещения?

1. При реализации своих классов
Если написали копирование и к нему нужно перемещение
2. Использование std::move для <тяжелых> объектов
3. Передача по значению и возврат из функций

Когда не следует?
1. С константами
2. С небольшими структурами
3. Когда хотим работать с исходным объектом

ПРАВИЛО ПЯТИ
Если ваш класс определяет хотя бы одну из пяти специальных функций-членов, связанных
с управлением ресурсами (динамическая память, файловые дескрипторы, сетевые соединения и т. д.),
то, скорее всего, он должен явно определить все пять:
1. Деструктор
2. Конструктор копирования
3. Оператор копирующего присваивания
4. Конструктор перемещения
5. Оператор перемещающего присваивания
*/