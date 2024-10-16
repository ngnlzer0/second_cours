#include<iostream>
#include<cmath>

// функція, яка створює нову матрицю
double** Create_Matrix(int SIZE) {
	double** matrix = new double* [SIZE];
	for (int i = 0; i < SIZE; ++i) {
		matrix[i] = new double[SIZE];
	}
	return matrix;
}

double** normal_multi(double** A, double** B, int SIZE)
{
	double** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				C[i][j] += A[i][k] * B[k][j];
	return C;
}

double** convertToDoublePointer(double arr[][4], const int SIZE) {
	double** matrix = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			matrix[i][j] = arr[i][j];

	return matrix;
}

//функція яка додає 2 матриці
double** Add_Matrix(double** A, double** B, const int SIZE)
{
	double** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; ++j)
			C[i][j] = A[i][j] + B[i][j];
	return C;
}

//функція яка віднімає 2 матриці
double** Subtraction_Matrix(double** A, double** B, const int SIZE)
{
	double** C = Create_Matrix(SIZE);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			C[i][j] = A[i][j] - B[i][j];
	return C;
}

double** Strassen_Algo(double** A, double** B, int SIZE)
{
	if (SIZE <= 2) // якщо в нас матриця невелика, то нам доцільніше просто звичайно їх перемножити
	{
		double** C = Create_Matrix(SIZE);
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				for (int k = 0; k < SIZE; k++)
					C[i][j] += A[i][k] * B[k][j];
		return C;
	}

	int half = SIZE / 2;

	//розбиваємо наші матриці на "підматриці"
	double** A11 = Create_Matrix(half);
	double** A12 = Create_Matrix(half);
	double** A21 = Create_Matrix(half);
	double** A22 = Create_Matrix(half);
	double** B11 = Create_Matrix(half);
	double** B12 = Create_Matrix(half);
	double** B21 = Create_Matrix(half);
	double** B22 = Create_Matrix(half);

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
	double** M1 = Strassen_Algo(Add_Matrix(A11, A22, half), Add_Matrix(B11, B22, half), half);
	double** M2 = Strassen_Algo(Add_Matrix(A21, A22, half), B11, half);
	double** M3 = Strassen_Algo(A11, Subtraction_Matrix(B12, B22, half), half);
	double** M4 = Strassen_Algo(A22, Subtraction_Matrix(B21, B11, half), half);
	double** M5 = Strassen_Algo(Add_Matrix(A11, A12, half), B22, half);
	double** M6 = Strassen_Algo(Subtraction_Matrix(A21, A11, half), Add_Matrix(B11, B12, half), half);
	double** M7 = Strassen_Algo(Subtraction_Matrix(A12, A22, half), Add_Matrix(B21, B22, half), half);

	//тепер шукаємо результуючі підматриці
	double** C11 = Add_Matrix(M7, Subtraction_Matrix(Add_Matrix(M1, M4, half), M5, half), half);
	double** C12 = Add_Matrix(M3, M5, half);
	double** C21 = Add_Matrix(M2, M4, half);
	double** C22 = Add_Matrix(Subtraction_Matrix(M1, M2, half), Add_Matrix(M3, M6, half), half);

	//обєднуємо наші підматриці, в фінальну матрицю
	double** C = Create_Matrix(SIZE);
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

void Show_Matrix(double** Mat, const int SIZE)
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

	double matrixA[4][4] = {
	{1.1, 2.2, 3.3, 4.4},
	{6.6, 7.7, 8.8, 9.9},
	{11.2, 12.3, 13.4, 14.5},
	{16.7, 17.8, 18.9, 19.1},
	};

	double matrixB[4][4] = {
		{0.5, 1.5, 2.5, 3.5},
		{5.5, 6.5, 7.5, 8.5},
		{10.5, 11.5, 12.5, 13.5},
		{15.5, 16.5, 17.5, 18.5},
	};


	double** A = convertToDoublePointer(matrixA, 4);
	double** B = convertToDoublePointer(matrixB, 4);

	std::cout << "Strassen algorithm for matrix multiplication: \n";
	double** C = Strassen_Algo(A, B, 4);
	Show_Matrix(C, 4);

	std::cout << "ordinary matrix multiplication: \n";
	double** N = normal_multi(A, B, 4);
	Show_Matrix(N, 4);


	return 0;
}