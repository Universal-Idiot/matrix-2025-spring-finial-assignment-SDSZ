#include "matrix.hpp"

int main()
{
	int rows, cols;
	std::cout << "\n\nPlease enter number of rows & columns: \n";
    std::cin >> rows >> cols;
    std::cout << "Please enter the matirx: \n";
	Matrix A(rows, cols);
	A.impart();
	A.RREF();
	A.printALLinfo();
	return 0;
}