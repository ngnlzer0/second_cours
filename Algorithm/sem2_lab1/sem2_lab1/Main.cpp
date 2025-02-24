#include<iostream>

// ідеальне хешування для дійсних чисел (подання даних йде вектором)
#include <iostream>
#include <cmath>
#include <limits>

class RealNumber {
private:
    double value;
    static constexpr double EPSILON = 1e-9;  // Похибка для порівняння

public:
    // Конструктори
    RealNumber() : value(0.0) {}
    RealNumber(double v) : value(v) {}

    // Спеціальні константи
    static RealNumber infinity() { return RealNumber(std::numeric_limits<double>::infinity()); }
    static RealNumber nan() { return RealNumber(std::numeric_limits<double>::quiet_NaN()); }

    // Арифметичні оператори
    RealNumber operator+(const RealNumber& other) const {
        return RealNumber(value + other.value);
    }

    RealNumber operator-(const RealNumber& other) const {
        return RealNumber(value - other.value);
    }

    RealNumber operator*(const RealNumber& other) const {
        return RealNumber(value * other.value);
    }

    RealNumber operator/(const RealNumber& other) const {
        if (std::abs(other.value) < EPSILON) {
            return RealNumber::infinity();
        }
        return RealNumber(value / other.value);
    }

    // Оператори порівняння з урахуванням похибки
    bool operator==(const RealNumber& other) const {
        if (std::isnan(value) || std::isnan(other.value)) return false;
        if (std::isinf(value) || std::isinf(other.value)) return value == other.value;
        return std::abs(value - other.value) < EPSILON;
    }

    bool operator!=(const RealNumber& other) const {
        return !(*this == other);
    }

    bool operator<(const RealNumber& other) const {
        return value < other.value - EPSILON;
    }

    bool operator>(const RealNumber& other) const {
        return value > other.value + EPSILON;
    }

    bool operator<=(const RealNumber& other) const {
        return !(*this > other);
    }

    bool operator>=(const RealNumber& other) const {
        return !(*this < other);
    }

    // Оператор приведення до double
    operator double() const {
        return value;
    }

    // Додаткові математичні функції
    RealNumber sqrt() const {
        if (value < 0) return RealNumber::nan();
        return RealNumber(std::sqrt(value));
    }

    RealNumber pow(double exponent) const {
        return RealNumber(std::pow(value, exponent));
    }

    RealNumber abs() const {
        return RealNumber(std::abs(value));
    }

    // Ввід/вивід
    friend std::ostream& operator<<(std::ostream& os, const RealNumber& num) {
        if (std::isinf(num.value)) os << "inf";
        else if (std::isnan(num.value)) os << "NaN";
        else os << num.value;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, RealNumber& num) {
        is >> num.value;
        return is;
    }
};

// Клас для представлення раціональних чисел (додатково)
#include <iostream>

class Fraction {
private:
    int numerator, denominator;

public:
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::runtime_error("Знаменник не може бути 0!");
        }
        if (denominator < 0) {  // Переносимо знак у чисельник
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Конструктор з `RealNumber`
    Fraction(double real) {
        int denom = 1;
        while (real != static_cast<int>(real) && denom < 1000000) {  // Обмежуємо знаменник
            real *= 10;
            denom *= 10;
        }
        numerator = static_cast<int>(real);
        denominator = denom;
        if (denominator < 0) {  // Знову переносимо знак у чисельник
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Перетворення у `double`
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Вивід
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }
};

class HashTable
{

};

int main() 
{
    setlocale(LC_CTYPE, "ukr");

    RealNumber a = 2.0, b = -9.0;
    std::cout << "Квадратний корінь з " << a << " = " << a.sqrt() << std::endl;
    std::cout << "Модуль " << b << " = " << b.abs() << std::endl;
    std::cout << "2^3 = " << a.pow(3) << std::endl;

    RealNumber inf = RealNumber::infinity();
    RealNumber nan = RealNumber::nan();
    std::cout << "Нескінченність: " << inf << std::endl;
    std::cout << "NaN: " << nan << std::endl;

    // Приклад дробу
    Fraction frac1(3, 4);
    std::cout << "Дріб: " << frac1 << " = " << static_cast<double>(frac1) << std::endl;

    Fraction frac2(RealNumber(0.75));
    std::cout << "Реальне число 0.75 як дріб: " << frac2 << std::endl;

    system("pause");
    return 1;
}