// lab6.cpp — лабораторная работа «CSV, JSON и свой тип Value»
//
// Схема:   test.csv  --read_csv-->  Value  --to_json-->  JSON-файл
//
// Нужен файл json.hpp (библиотека nlohmann/json) — положите его рядом с lab6.cpp.
// Сборка:  g++ -std=c++17 -Wall -Wextra lab6.cpp -o lab6
//
// Запуск:
//   ./lab6 csv test.csv                  прочитать CSV и напечатать строки
//   ./lab6 csv2json test.csv out.json    CSV -> JSON-файл
//
// ЧТО ДЕЛАТЬ: найдите слова TODO и допишите код (их 8, по порядку сверху вниз).
// Класс Null — образец: посмотрите, как он устроен, и сделайте Bool, Number, String так же.
// Всё остальное (Array, Object, main, вспомогательные функции) уже готово.

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
// JSON-BEGIN
#include "json.hpp"
using json = nlohmann::json;
// JSON-END

// ====================================================================
//  Часть 1. Свой тип Value (наследование + виртуальные методы)
// ====================================================================
// Value — «любое значение JSON». Конкретные виды значений — наследники.
// Каждый наследник сам умеет превратить себя в текст (to_string).

struct Value;
using ValuePtr = std::unique_ptr<Value>;   // умный указатель: сам удалит объект

struct Value {
    virtual ~Value() = default;
    virtual std::string to_string() const = 0;   // = 0: у Value нет своей реализации
};

// ОБРАЗЕЦ: null
struct Null : Value {
    std::string to_string() const override { return "null"; }
};

// Строка в кавычках для вывода: слово -> "слово" (готово)
std::string quote(const std::string& s) {
    std::string r = "\"";
    for (char c : s) {
        if (c == '"' || c == '\\') r += '\\';
        r += c;
    }
    return r + "\"";
}

// ---------- TODO 1. Bool: true / false ----------
// to_string: "true" или "false".
struct Bool : Value {
    bool value;
    explicit Bool(bool v) : value(v) {}
    std::string to_string() const override {
        // TODO 1
        return value ? "true" : "false";
        //
    }
};

// ---------- TODO 2. Number: число ----------
// to_string: число без лишних нулей (19 -> "19", 4.5 -> "4.5").
// Подсказка: std::ostringstream out; out.precision(15); out << value; return out.str();
struct Number : Value {
    double value;
    explicit Number(double v) : value(v) {}
    std::string to_string() const override {
        // TODO 2
        std::ostringstream out;
        out.precision(15);
        out << value;
        return out.str();
        //
    }
};

// ---------- TODO 3. String: строка ----------
// to_string: строка в кавычках — используйте готовую quote(value).
struct String : Value {
    std::string value;
    explicit String(std::string v) : value(std::move(v)) {}
    std::string to_string() const override {
        // TODO 3
        return quote(value);
        //
    }
};

// Array и Object — готовы. Прочитайте, как они печатают вложенные значения:
// у каждого элемента вызывается его to_string() — «правильная» версия выбирается сама.
struct Array : Value {
    std::vector<ValuePtr> items;
    std::string to_string() const override {
        std::string r = "[";
        for (std::size_t i = 0; i < items.size(); ++i) {
            if (i > 0) r += ", ";
            r += items[i]->to_string();
        }
        return r + "]";
    }
};

struct Object : Value {
    std::map<std::string, ValuePtr> fields;
    std::string to_string() const override {
        std::string r = "{";
        bool first = true;
        for (const auto& [key, val] : fields) {
            if (!first) r += ", ";
            r += quote(key) + ": " + val->to_string();
            first = false;
        }
        return r + "}";
    }
};

// Шаблон (готов): узнать, какой тип лежит внутри Value.
// as<Number>(v) вернёт указатель на Number, а если там другой тип — nullptr.
//   if (const Number* n = as<Number>(v)) { ... n->value ... }
template <typename T>
const T* as(const Value& v) {
    return dynamic_cast<const T*>(&v);
}

// ====================================================================
//  Часть 2. CSV -> Value
// ====================================================================

// ---------- TODO 4. split ----------
// Делит строку по разделителю:  split("a,b,,d", ',')  ->  {"a", "b", "", "d"}
// Подсказка: std::istringstream in(line);  while (std::getline(in, part, sep)) ...
// Ловушка: у строки "a,b," последнее поле пустое, а getline его не вернёт —
// если line заканчивается на sep, добавьте в конец пустую строку.
std::vector<std::string> split(const std::string& line, char sep) {
    // TODO 4
    std::vector<std::string> parts;
    std::istringstream in(line);
    std::string part;
    while (std::getline(in, part, sep)) parts.push_back(part);
    // добавляем последнее пустое поле вручную
    if (!line.empty() && line.back() == sep) parts.push_back("");
    return parts;
}

// Готово: проверяет, что text — число целиком, и кладёт его в result.
//   double d; if (is_number("4.5", d)) ...  // true, d == 4.5;   is_number("abc", d) -> false
bool is_number(const std::string& text, double& result) {
    try {
        std::size_t pos = 0;
        result = std::stod(text, &pos);
        return pos == text.size() && std::isfinite(result);
    } catch (const std::exception&) {
        return false;    // stod не смог разобрать, например "abc"
    }
}

// ---------- TODO 5. parse_field ----------
// Превращает текст ячейки в Value:
//   ""            -> Null
//   "true"/"false"-> Bool
//   число (4.5)   -> Number    (проверка — готовая is_number)
//   всё остальное -> String
// Подсказка: return std::make_unique<Number>(d);
ValuePtr parse_field(const std::string& text) {
    // TODO 5
    if (text.empty()) return std::make_unique<Null>();
    if (text == "true") return std::make_unique<Bool>(true);
    if (text == "false") return std::make_unique<Bool>(false);
    double d;
    if (is_number(text, d)) return std::make_unique<Number>(d);
    return std::make_unique<String>(text);
    //
}

void strip_cr(std::string& line) {   // готово: убирает '\r' в файлах из Windows
    if (!line.empty() && line.back() == '\r') line.pop_back();
}

// ---------- TODO 6. read_csv ----------
// Читает CSV-файл (первая строка — заголовок) и возвращает Array из Object:
// каждая строка файла -> один Object, где ключ — имя колонки из заголовка.
//
// Шаги:
//   1. std::ifstream in(path); если не открылся — throw std::runtime_error("cannot open " + path);
//   2. прочитать первую строку (std::getline), strip_cr, header = split(строка, ',')
//   3. в цикле читать строки: пустые пропускать; cells = split(строка, ',');
//      если cells.size() != header.size() — throw std::runtime_error(...)
//   4. создать Object, для каждой колонки: row->fields[header[i]] = parse_field(cells[i]);
//   5. добавить в Array: table->items.push_back(std::move(row));
ValuePtr read_csv(const std::string& path) {
    // TODO 6
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open " + path);

    std::string line;
    if (!std::getline(in, line)) throw std::runtime_error("cannot read " + path);
    strip_cr(line);
    auto header = split(line, ',');

    auto table = std::make_unique<Array>();
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto cells = split(line, ',');
        if (cells.size() != header.size()) throw std::runtime_error("incorrect line size");
        auto row = std::make_unique<Object>();
        for (std::size_t i = 0; i < header.size(); ++i) row->fields[header[i]] = parse_field(cells[i]);
        table->items.push_back(std::move(row));
    }
    return table;
    //
}

// ====================================================================
//  Часть 3. Value -> JSON (библиотека nlohmann/json)
// ====================================================================
// Основное из библиотеки:
//   json::array(), json::object()          пустой массив / объект JSON
//   result.push_back(x)                    добавить в массив
//   result[key] = x                        записать поле объекта
//   j.dump(2)                              текст JSON с отступом 2
// Присваивание работает для разных типов: json j = true; j = 4.5; j = "text"; j = nullptr;
// (внутри библиотеки это шаблоны).

// JSON-BEGIN
// ---------- TODO 7. to_json ----------
// Value -> JSON. Тип узнаём через as<T>:  if (auto b = as<Bool>(v)) return b->value;
// Допишите ветки Null, Bool, Number, String. Ветки Array и Object готовы — посмотрите,
// как они вызывают to_json рекурсивно для вложенных значений.
// Для Number: целые числа лучше отдавать как целые, чтобы в файле было 19, а не 19.0:
//   if (n->value == std::floor(n->value)) return static_cast<long long>(n->value);
json to_json(const Value& v) {
    // TODO 7: ветки для Null, Bool, Number, String
    if (as<Null>(v)) return nullptr;
    if (auto b = as<Bool>(v)) return b->value;
    if (auto n = as<Number>(v)) {
        if (n->value == std::floor(n->value) && std::fabs(n->value) < 1e15)
            return static_cast<long long>(n->value);
        return n->value;
    }
    if (auto s = as<String>(v)) return s->value;
    //
    if (auto a = as<Array>(v)) {
        json result = json::array();
        for (const auto& item : a->items) result.push_back(to_json(*item));
        return result;
    }
    if (auto o = as<Object>(v)) {
        json result = json::object();
        for (const auto& [key, val] : o->fields) result[key] = to_json(*val);
        return result;
    }
    throw std::runtime_error("unknown Value type");
}

// ---------- TODO 8. from_json: JSON -> Value ----------
// Нужна для команды json. Проверяйте тип по очереди:
//   j.is_null(), j.is_boolean(), j.is_number(), j.is_string(), j.is_array()
// Достать значение:  j.get<bool>(), j.get<double>(), j.get<std::string>()  (это шаблон!)
// Массив: for (const auto& element : j) ...     Объект: for (auto& [key, value] : j.items()) ...
// Для массива и объекта вызывайте from_json рекурсивно.
ValuePtr from_json(const json& j) {
    // TODO 8
    if (j.is_null()) return std::make_unique<Null>();
    if (j.is_boolean()) return std::make_unique<Bool>(j.get<bool>());
    if (j.is_number()) return std::make_unique<Number>(j.get<double>());
    if (j.is_string()) return std::make_unique<String>(j.get<std::string>());
    if (j.is_array()) {
        auto arr = std::make_unique<Array>();
        for (const auto& element : j) arr->items.push_back(from_json(element));
        return arr;
    }
    if (j.is_object()) {
        auto obj = std::make_unique<Object>();
        for (auto& [key, value] :
            j.items()) obj->fields[key] = from_json(value);
        return obj;
    }
    throw std::runtime_error("unknown JSON type");
}
// JSON-END

// Массив печатаем по одному элементу в строке, остальное — одной строкой (готово).
void print_rows(const Value& v) {
    if (const Array* array = as<Array>(v)) {
        for (const auto& item : array->items) std::cout << item->to_string() << "\n";
    } else {
        std::cout << v.to_string() << "\n";
    }
}

// ====================================================================
//  Команды и main (готово, менять не нужно)
// ====================================================================

using Args = std::vector<std::string>;

int usage() {
    std::cerr << "Использование:\n"
                 "  lab6 csv ФАЙЛ.csv\n"
                 "  lab6 csv2json ФАЙЛ.csv РЕЗУЛЬТАТ.json\n"
                 "  lab6 json ФАЙЛ.json\n";
    return 1;
}

int cmd_csv(const Args& args) {
    if (args.size() != 1) return usage();
    print_rows(*read_csv(args[0]));
    return 0;
}

// JSON-BEGIN
int cmd_csv2json(const Args& args) {
    if (args.size() != 2) return usage();
    ValuePtr table = read_csv(args[0]);
    std::ofstream out(args[1]);
    if (!out) throw std::runtime_error("cannot write " + args[1]);
    out << to_json(*table).dump(2) << "\n";
    return 0;
}

int cmd_json(const Args& args) {
    if (args.size() != 1) return usage();
    std::ifstream in(args[0]);
    if (!in) throw std::runtime_error("cannot open " + args[0]);
    print_rows(*from_json(json::parse(in)));
    return 0;
}
// JSON-END

int main(int argc, char* argv[]) {
    if (argc < 2) return usage();
    const std::string name = argv[1];
    const Args args(argv + 2, argv + argc);
    try {
        if (name == "csv") return cmd_csv(args);
        if (name == "csv2json") return cmd_csv2json(args);   // JSON-LINE
        if (name == "json") return cmd_json(args);           // JSON-LINE
    } catch (const std::exception& e) {
        std::cerr << "lab6 " << name << ": " << e.what() << "\n";
        return 1;
    }
    std::cerr << "lab6: неизвестная команда: " << name << "\n";
    return usage();
}
