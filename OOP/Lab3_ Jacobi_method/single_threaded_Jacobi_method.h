#pragma once
#include <vector>

/// <summary>
/// This is a class that implements an approximate iterative solution
/// to a system of linear equations.
/// This class does everything in one thread  
/// </summary>

class single_threaded_Jacobi_method
{
protected:
	std::vector<std::vector<double>> A; // is the matrix A with coefficients at x[i][j]
	std::vector<double> X; // is the vector of desired coefficients
	std::vector<double> B; // vector column B
	std::vector<std::vector<double>> R; // is a matrix containing elements from the diagonal of matrix A, all other elements are zero
	std::vector<std::vector<double>> D; // is a matrix containing all elements except the diagonal ones from matrix A, the diagonal ones are zero
	int SIZE; // the number of unknowns, and the sizes of matrices and vectors

	/// <summary>
	/// decoupling matrix A to R and D
	/// </summary>
	void decoupling();

	/// 
	/// @param i number the row
	/// @param x currently vector solution
	///
	/// This function find a sum product to R[i][j] * x[j] = SUM
	/// 
	/// @return SUM
	double SumR(int i, std::vector<double>& x);

public:
	/// <summary>
	/// basic constructor
	/// </summary>
	single_threaded_Jacobi_method();


	/// <summary>
	///
	/// a basic constructor that initializes our matrix and vector
	/// 
	/// </summary>
	/// <param name="a"> the matrix A</param>
	/// <param name="b"> the vector B</param>
	/// <param name="size"> size a matrixs and vectors</param>
	single_threaded_Jacobi_method(std::vector<std::vector<double>> a, std::vector<double> b, int size);


	///
	/// The main method, that performs the main algorithm
	/// algorithm looks like:
	///
	/// 1)
	/// First, we check whether our matrix A, the diagonal-dominant:
	///  If so, we can use this algorithm and move on, if not, this algorithm will not work and return;
	/// 2) We have vector X_prev and X_cur which are initially zero
	/// 3) then we search for each Xi step by step by the formula:
	///        x_cur[i] = (1.0 / D[i][i]) * (B[i] - SumR(i, x_prev));
	///  and repeat this step until this condition is met: (x_cur[i] - x_prev[i]) > epsilo)
	/// if the condition is fulfilled for each element X, our algorithm terminates
	/// @param epsilo the accuracy of our unknowns
	virtual void Main_method(double epsilo);

	/// <summary>
	/// This Function Show our shows our unknowns(X[i])
	/// </summary>
	void ShowX();

	/// <summary>
	/// this function checks whether our matrix A is diagonally dominated by the formula :
	/// |a[i][i]| >= ? (|a[i][j]|) ;
	/// if this is done for all rows, then the matrix is diagonally dominated, otherwise it is not
	/// </summary>
	/// <returns></returns>
	bool Check_working_method();

	/// <summary>
	/// geting a number in index i, for a doctest or other
	/// </summary>
	/// <param name="i">index the element in vector</param>
	/// <returns></returns>
	double Get_Xi(int i) { return X[i]; };
};

