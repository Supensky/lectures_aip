#include <iostream>
#include <stdexcept>
#include <algorithm>

class Interval {
private:
    double a_, b_;
public:
    // Конструкторы
    Interval(double a, double b) : a_(a), b_(b) {
        if (a > b) {
            throw std::invalid_argument("Left interval is greater than or equal to right.");
        }
    }
    Interval(double x = 0.0) : a_(x), b_(x) {}

    // Геттеры
    double lower() const { return a_; }
    double upper() const { return b_; }

    // Интервал содержит 0
    bool contains_zero() const { return a_ <= 0.0 && 0.0 <= b_; }

    // Унарный минус
    Interval operator-() const { return Interval(-b_, -a_); }
    // Сложение
    Interval operator+(const Interval& i) const {
        return Interval(a_ + i.a_, b_ + i.b_);
    }
    // Вычитание
    Interval operator-(const Interval& i) const {
        return Interval(a_ - i.b_, b_ - i.a_);
    }
    // Умножение
    Interval operator*(const Interval& i) const {
        double r1 = a_ * i.a_;
        double r2 = a_ * i.b_;
        double r3 = b_ * i.a_;
        double r4 = b_ * i.b_;
        return Interval(std::min({r1, r2, r3, r4}), std::max({r1, r2, r3, r4}));
    }
    // Деление
    Interval operator/(const Interval& i) const {
        if (i.contains_zero()) {
            throw std::domain_error("Division by zero.");
        }
        return *this * Interval(1.0 / i.b_, 1.0 / i.a_);
    }
};

std::ostream& operator<<(std::ostream& os, const Interval& i) {
    return os << '[' << i.lower() << ", " << i.upper() << ']';
}

int main() {
    Interval x(1, 2), y(3, 5);

    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";

    std::cout << "x + y = " << x + y << "\n";
    std::cout << "x - y = " << x - y << "\n";
    std::cout << "x * y = " << x * y << "\n";
    std::cout << "x / y = " << x / y << "\n";

    Interval z(-2, 4), w(-3, -1);
    std::cout << "z * w = " << z * w << "\n";
    std::cout << "x / w = " << x / w << "\n";

    try {
        std::cout << x / z << "\n";
    } catch (const std::domain_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}