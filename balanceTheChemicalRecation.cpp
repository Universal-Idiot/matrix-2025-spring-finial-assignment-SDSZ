#include "matrix.hpp"

int main()
{
    int rows, cols, size;

    std::cout << "\nReactant:\nPlease enter number of element: \n";
    std::cin >> rows;
    std::cout << "\nReactant:\nPlease enter number of element: \n";
    std::cout << "Please enter the matirx: \n";
    Matrix R(rows, cols);
    R.impart();
    std::cout << "\n\nPlease enter number of rows & columns: \n";
    std::cin >> cols;
    std::cout << "Please enter the matirx: \n";
    Matrix P(rows, cols);
    P.impart();

    P = -1 * P;
    Matrix input = CombineMatrix(R, P, 'H');

    Vector zero(input.getNumOfrow());
    zero.fill(0);

    solutionOfLinearEquation x;
    x = SolveLinearEquation(input, zero);

    x.print();

    return 0;
}