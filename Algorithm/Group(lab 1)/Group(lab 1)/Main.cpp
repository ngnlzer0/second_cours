#include<iostream>
#include<cmath>
#include <stdexcept>
#include <numeric> // для std::gcd в C++17 або новіше

class Rational {
private:
	int numerator;
	int denominator;

	void simplify() {
		int gcd = std::gcd(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;

		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
	}

public:
	// Конструктор для чисел з плаваючою точкою
	Rational(double value) {
		const int precision = 1000000; // Наприклад, 6 цифр точності
		numerator = static_cast<int>(value * precision);
		denominator = precision;
		simplify();
	}

	// Залишаємо попередній конструктор для цілих чисел
	Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
		if (denom == 0) {
			throw std::invalid_argument("Знаменник не може бути нулем");
		}
		simplify();
	}

	// Операції додавання
	Rational operator+(const Rational& other) const {
		int num = numerator * other.denominator + other.numerator * denominator;
		int denom = denominator * other.denominator;
		return Rational(num, denom);
	}

	// Операції віднімання
	Rational operator-(const Rational& other) const {
		int num = numerator * other.denominator - other.numerator * denominator;
		int denom = denominator * other.denominator;
		return Rational(num, denom);
	}

	// Операція множення
	Rational operator*(const Rational& other) const {
		int num = numerator * other.numerator;
		int denom = denominator * other.denominator;
		return Rational(num, denom);
	}

	// Операція ділення
	Rational operator/(const Rational& other) const {
		if (other.numerator == 0) {
			throw std::invalid_argument("Ділення на нуль");
		}
		int num = numerator * other.denominator;
		int denom = denominator * other.numerator;
		return Rational(num, denom);
	}

	// Вивід раціонального числа
	friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
		os << r.numerator;
		if (r.denominator != 1) {
			os << '/' << r.denominator;
		}
		return os;
	}
};

// функція, яка створює нову матрицю
Rational** Create_Matrix(int SIZE) {
	Rational** matrix = new Rational * [SIZE];
	for (int i = 0; i < SIZE; ++i) {
		matrix[i] = new Rational[SIZE];
	}
	return matrix;
}

Rational** normal_multi(Rational** A, Rational** B, int SIZE)
{
	Rational** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
	return C;
}

Rational** convertToDoublePointer(Rational arr[][4], const int SIZE) {
	Rational** matrix = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			matrix[i][j] = arr[i][j];

	return matrix;
}

//функція яка додає 2 матриці
Rational** Add_Matrix(Rational** A, Rational** B, const int SIZE)
{
	Rational** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; ++j)
			C[i][j] = A[i][j] + B[i][j];
	return C;
}

//функція яка віднімає 2 матриці
Rational** Subtraction_Matrix(Rational** A, Rational** B, const int SIZE)
{
	Rational** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			C[i][j] = A[i][j] - B[i][j];
	return C;
}

Rational** Strassen_Algo(Rational** A, Rational** B, int SIZE)
{
	if (SIZE <= 2) // якщо в нас матриця невелика, то нам доцільніше просто звичайно їх перемножити
	{
		Rational** C = Create_Matrix(SIZE);
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				for (int k = 0; k < SIZE; k++)
					C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
		return C;
	}

	int half = SIZE / 2;

	//розбиваємо наші матриці на "підматриці"
	Rational** A11 = Create_Matrix(half);
	Rational** A12 = Create_Matrix(half);
	Rational** A21 = Create_Matrix(half);
	Rational** A22 = Create_Matrix(half);
	Rational** B11 = Create_Matrix(half);
	Rational** B12 = Create_Matrix(half);
	Rational** B21 = Create_Matrix(half);
	Rational** B22 = Create_Matrix(half);

	//ініціалізуємо наші підматриці
	for (int i = 0; i < half; i++)
		for (int j = 0; j < half; j++)
		{
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + half];
			A21[i][j] = A[i + half][j];
			A22[i][j] = A[i + half][j + half];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + half];
			B21[i][j] = B[i + half][j];
			B22[i][j] = B[i + half][j + half];
		}

	//обчислюємо допоміжні підматриці
	Rational** M1 = Strassen_Algo(Add_Matrix(A11, A22, half), Add_Matrix(B11, B22, half), half);
	Rational** M2 = Strassen_Algo(Add_Matrix(A21, A22, half), B11, half);
	Rational** M3 = Strassen_Algo(A11, Subtraction_Matrix(B12, B22, half), half);
	Rational** M4 = Strassen_Algo(A22, Subtraction_Matrix(B21, B11, half), half);
	Rational** M5 = Strassen_Algo(Add_Matrix(A11, A12, half), B22, half);
	Rational** M6 = Strassen_Algo(Subtraction_Matrix(A21, A11, half), Add_Matrix(B11, B12, half), half);
	Rational** M7 = Strassen_Algo(Subtraction_Matrix(A12, A22, half), Add_Matrix(B21, B22, half), half);

	//тепер шукаємо результуючі підматриці
	Rational** C11 = Add_Matrix(M7, Subtraction_Matrix(Add_Matrix(M1, M4, half), M5, half), half);
	Rational** C12 = Add_Matrix(M3, M5, half);
	Rational** C21 = Add_Matrix(M2, M4, half);
	Rational** C22 = Add_Matrix(Subtraction_Matrix(M1, M2, half), Add_Matrix(M3, M6, half), half);

	//обєднуємо наші підматриці, в фінальну матрицю
	Rational** C = Create_Matrix(SIZE);
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			C[i][j] = C11[i][j];
			C[i][j + half] = C12[i][j];
			C[i + half][j] = C21[i][j];
			C[i + half][j + half] = C22[i][j];
		}
	}
	return C;
}

void Show_Matrix(Rational** Mat, const int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			std::cout << Mat[i][j] << "\t ";
		}
		std::cout << "\n";
	}
}

int main()
{

	Rational matrixA[4][4] = {
	{1.1, 2.2, 3.3, 4.4},
	{6.6, 7.7, 8.8, 9.9},
	{11.2, 12.3, 13.4, 14.5},
	{16.7, 17.8, 18.9, 19.1},
	};

	Rational matrixB[4][4] = {
		{0.5, 1.5, 2.5, 3.5},
		{5.5, 6.5, 7.5, 8.5},
		{10.5, 11.5, 12.5, 13.5},
		{15.5, 16.5, 17.5, 18.5},
	};


	Rational** A = convertToDoublePointer(matrixA, 4);
	Rational** B = convertToDoublePointer(matrixB, 4);

	std::cout << "Strassen algorithm for matrix multiplication: \n";
	Rational** C = Strassen_Algo(A, B, 4);
	Show_Matrix(C, 4);

	std::cout << "ordinary matrix multiplication: \n";
	Rational** N = normal_multi(A, B, 4);
	Show_Matrix(N, 4);


	return 0;
}