#include "matrix.hpp"

int main()
{
	int rows, cols;
	while(1){
	std::cout << "\n\nPlease enter number of rows & columns: \n";
    std::cin >> rows >> cols;
    std::cout << "Please enter the matirx: \n";
	Matrix_f A(rows, cols);
	A.impartInt();
	A.RREF();
	A.printALLinfo(); //
	}
	return 0;
}