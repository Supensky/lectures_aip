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
    vector<int> v; // пустой векторэ

    // --- Добавление ---
    v.push_back(10); // добавляем в конец
    v.push_back(20);
    v.emplace_back(30);
    v.insert(v.begin() + 1, 99); // вставить 99 на позицию 1 -> {10, 99, 20, 30}

    // --- Размер и емкость ---
    cout << v.size() << " " << v.capacity() << " " << v.empty() << "\n";
    v.reserve(50); // зарезервировать память (без реллокаций при росте)

    // --- Доступ ---
    cout << v[0] << " " << v.at(1) << " " << v.front() << " " << v.back() << "\n";
    int* raw = v.data(); // указатель на непрерывный буфер

--------


*/