#include "matrix.hpp"

// matrix.cpp
// Implementation of Linear Algebra classes
// Author: 11767（文俊钦）
// Date: 2025-5-14
// 哦天哪还没写多少呢已经成一坨屎山了……而且一些东西还是AI现教我的。

// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// Vector: 

Vector::Vector(int d) : size(d)
{
    data = new Number[size];
}

Vector::Vector()
{
    size = 1;
    data = nullptr;
}

Vector::~Vector()
{
    if(data)
        delete[] data;
}

void Vector::impart()
{
    for(int i = 0; i < size; i++) 
            std::cin >> data[i];
}    

void Vector::print()
{
    for(int i = 0; i < size; i++) 
    {
        std::cout << data[i] << ' ';
    }
}

void Vector::fill(Number a)
{
    for(int i = 0; i < size; i++) 
        data[i] = a;
}

void Vector::add(Number a) // add a at the end // waiting for update: avoiding allocating memories frequently, by adding capacity(maybe = 2 * size) in advance, only when size is bigger than capacity will try to allocate new memorires
{
    if(data == nullptr)
    {
        data = new Number[1];
        size = 1;
        data[0] = a;
        return;
    }
    Vector temp(size + 1);
    for(int i = 0; i < size; i++)
        temp.data[i] = data[i];
    temp.data[size] = a;
    delete[] data;
    size+=1;
    data = new Number[size];
    for(int i = 0; i < size; i++)
        data[i] = temp.data[i];
}

int Vector::getSize()
{
    return size;
}

Vector& Vector::operator=(const Vector& right)
{
    if(this != &right)
    {
        // delete old memory
        if(data)
            delete[] data;
        size = right.size;
        // create new memory
        data = new Number[size];
        for(int i = 0; i < size; i++)
            data[i] = right.data[i];
    }
    return *this;
}

// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// Matrix:

Matrix:: Matrix(int r, int c) : rows(r), cols(c), rank(-1)
{
    if(rows <= 0 || cols <= 0)
    {
        PrintSadCat();
        assert(false);
    }
    data = new Number*[rows];
    for(int i = 0; i < rows; i++)
        data[i] = new Number[cols];
    PositionOfPivot.data = nullptr;
}

Matrix:: Matrix(int size) : rows(size), cols(size), rank(-1)
{
    data = new Number*[rows];
    for(int i = 0; i < rows; i++)
    {
        data[i] = new Number[cols];
        for(int j = 0; j < cols; j++)
            if(i == j) data[i][j] = 1;
            else data[i][j] = 0;
    }
    PositionOfPivot.data = nullptr;
}

Matrix::Matrix() : rank(-1)
{
    rows = 1;
    cols = 1;
    data = new Number*[rows];  
    for(int i = 0; i < rows; i++)
        data[i] = new Number[cols];
    PositionOfPivot.data = nullptr;
}

Matrix::Matrix(char c) : rows(0), cols(0), rank(-1) // actually, this constructor function should be "Matrix();", but i have already define that function, and i aren't sure is any other function uses this feature that "Matrix a;" will create a 1*1 matrix
{
    data = nullptr;
    PositionOfPivot.data = nullptr;
}


Matrix::Matrix(const Matrix& right) : rows(right.rows), cols(right.cols), rank(right.rank)
{
    data = new Number*[rows];
    for(int i = 0; i < rows; i++)
    {
        data[i] = new Number[cols];
        for(int j = 0; j <  cols; j++)
        {
            data[i][j] = right.data[i][j];
        }
    }
    if(right.PositionOfPivot.data)
        {
            PositionOfPivot.data = new Number[cols];
            for(int i = 0; i < cols; i++)
                PositionOfPivot.data[i] = right.PositionOfPivot.data[i];
        }
    else    
        PositionOfPivot.data = nullptr;
}

Matrix::~Matrix()
{
    if(data)
    {
        for(int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }
    // class vector have a destroyer function
}

void Matrix::impart()
{
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
            std::cin >> data[i][j];
}  

void Matrix::print()
{
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            if(abs(data[i][j]) < epsilon)
                data[i][j] = 0;
            std::cout << data[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Matrix::print(int digit)
{
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            if(abs(data[i][j]) < epsilon)
                data[i][j] = 0;
            std::cout << std::fixed << std::setprecision(digit) << data[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Matrix::printALLinfo()
{
    std::cout << "\n\nrows: " << rows << "\ncolumns: " << cols;
    std::cout << "\nthe matrix is: \n";
    print();
    std::cout << "rank: ";
    if(rank == -1)
        std::cout<< "not compute yet";
    else    
        std::cout<< rank;
    std::cout << "\nthe position of pivots: ";
    if(PositionOfPivot.data)
        for(int i = 0; i < cols; i++)
            std::cout << PositionOfPivot.data[i] << ' ';
    else
        std::cout<< "not compute yet";
    PrintCat();
}

int Matrix::getNumOfColumn()
{
    return cols;
}

int Matrix::getNumOfrow()
{
    return rows;
}

Number Matrix::getData(int r, int c)
{
    return data[r][c];
}

void Matrix::fill(Number a)
{
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
            data[i][j] = a;
}

void Matrix::ErrorToZero()
{
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
            if(abs(data[i][j]) < epsilon)
                data[i][j] = 0;
}

Vector Matrix::RowOfMatrix(int Num_r) const
{
    Vector ans(cols);
    for(int i = 0; i < cols; i++)
        ans.data[i] = data[Num_r][i];
    return ans;
}

Vector Matrix::ColumnOfMatrix(int Num_c) const
{
    Vector ans(rows);
    for(int i = 0; i < rows; i++)
        ans.data[i] = data[i][Num_c];
    return ans;
}

void Matrix::RowOperation_MultiplyScalar(int Num_r, Number Num)
{
    if (Num_r < 0 || Num_r >= rows) 
    {
        std::cout << "Error: the number of rows is NOT applicable to excecute an expected row operation.\n";
        PrintSadCat();
        assert(false);
    }
    for(int i = 0; i < cols; i++)
        data[Num_r][i] = Num * data[Num_r][i];
}

void Matrix::RowOperation_ExchangeRow(int Num_r_1, int Num_r_2)
{
    if(Num_r_1 == Num_r_2)
        return;
    if (Num_r_1 < 0 || Num_r_1 >= rows || Num_r_2 < 0 || Num_r_2 >= rows) 
    {
        std::cout << "Error: the number of rows is NOT applicable to excecute an expected row operation.\n";
        PrintSadCat();
        assert(false);
    }
    Vector temp(cols);
    temp = RowOfMatrix(Num_r_1);
    for(int i = 0; i < cols; i++)
        data[Num_r_1][i] = data[Num_r_2][i];
    for(int i = 0; i < cols; i++)
        data[Num_r_2][i] = temp.data[i];
}

void Matrix::RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, Number Num) // Num_r_1 is the row you are operating, Num_r_2 is the another row you want to add to Num_r_1
{
    if (Num_r_1 == Num_r_2 || Num_r_1 < 0 || Num_r_1 >= rows || Num_r_2 < 0 || Num_r_2 >= rows) 
    {
        std::cout << "Error: the number of rows is NOT applicable to excecute an expected row operation.\n";
        PrintSadCat();
        assert(false);
    }
    for(int i = 0; i < cols; i++)
        data[Num_r_1][i] += Num * data[Num_r_2][i];
}

void Matrix::REF() // to ROW ECHELON FORM
{
    PositionOfPivot.data = new Number[cols];
    PositionOfPivot.size = cols;
    rank = 0;
    Number temp = 1; // storing the coefficient
    bool ifLoop = false;
    int position = 0; // row of last pivot
    for(int j = 0; j < cols; j++)// processing column by column
    {
        for(int i = position; i < rows; i++)// find a non-zero pivot, if no non-zero pivot in this column, move to the next column
        {
            if(data[i][j] != 0)
            {
                RowOperation_ExchangeRow(i, position);
                rank++;
                PositionOfPivot.data[j] = position + 1;
                ifLoop = true;
                position++;
                break;
            }
        }
        if(ifLoop == false)
        {
            PositionOfPivot.data[j] = 0;
            continue;
        }
        for(int i = position; i < rows; i++) // excute row reduction
        {
            if(data[i][j] == 0)
                continue;
            temp = -1*(data[i][j] / data[position - 1][j]);
            RowOperation_AddOneRowToAnother(i, position - 1, temp);
        }
        ifLoop = false;
    }
    ErrorToZero();
}

int Matrix::Rank()
{
    if(rank >= 0)
        return rank;
    else
    {
        REF();
        std::cout<<"coming soon qwq";
        PrintCat();
    }
    return rank;
}

Number Matrix::Det() // determiant
{
    if(rows != cols)
    {
        std::cout << "Error: only square have determiant";
        PrintSadCat();
        assert(false);
    }
    else if(rank < rows && rank > 0)
        return 0;
    else if(rows == 1)
        return data[0][0];
    else if(rows == 2)
        return ((data[0][0]*data[1][1])-(data[0][1]*data[1][0]));
	//此处应该用递归算法算5阶一下的，但是懒得开发了。之后再说吧，然后还得开发一个分块矩阵的函数
    else if(rows >= 3)
    {
        Number det = 0;
        Matrix temp(*this);
        temp.REF();
        det = temp.data[0][0];
        for(int i = 1; i < rows; i++)
            det *= temp.data[i][i];
        if(abs(det) < epsilon)
            det = 0;
        return det;
    }
    else
    {
        std::cout<<"Error: unknown error, ask Emma";
        PrintSadCat();
        assert(false);
    }
}

void Matrix::RREF()
{
    Number temp;
    REF();
    for(int i=0;i<cols;i++)
    {
        if(PositionOfPivot.data[i] == 0)
            continue;
        for(int j = rows - 1; j >= 0; j--)
        {
            if(data[j][i]!= 0)
            {
                temp = 1 / data[j][i];
                RowOperation_MultiplyScalar(j, temp);
                break;
            }
            else
                continue;
        }
    }
    ErrorToZero();
}
        
Matrix& Matrix::operator=(const Matrix& right)
{
    if(this != &right)
    {
        // delete old memory
        if(data)
        {
            for(int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;
        }
        // create new memory
        rows = right.rows;
        cols = right.cols;
        rank = right.rank;
        data = new Number*[rows];
        for(int i = 0; i < rows; i++)
        {
            data[i] = new Number[cols];
            for(int j = 0; j <  cols; j++)
            {
                data[i][j] = right.data[i][j];
            }
        }
        if(right.PositionOfPivot.data)
        {
            PositionOfPivot.data = new Number[cols];
            for(int i = 0; i < cols; i++)
                PositionOfPivot.data[i] = right.PositionOfPivot.data[i];
        }
    }
    return *this;
}

// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________________
// Others:

bool operator== (const Vector& left, const Vector& right)
{
    if(left.size != right.size)
        return false;
    for(int i = 0; i < right.size; i++) 
        if(right.data[i] != left.data[i])
            return false;
    return true;
}

Vector operator* (Number num, const Vector& right)
{
   Vector ans(right.size);
    for(int i = 0; i < ans.size; i++) 
        ans.data[i] = num * right.data[i];
    return ans;
}

Number operator* (Vector left, Vector right)// dot product
{
    // check size of two matrix
    if (!(left.size == right.size))
    {
        std::cout << "Error: vectors are not same size, cannot multiply.\n";
        std::cout << "left vector {";
        left.print();
        std::cout << "} have size of " << left.size << '\n';
        std::cout << "right vector {";
        right.print();
        std::cout << "} have size of " << right.size << '\n';
        PrintSadCat();
        assert(false);
    }
    // multiplication
    Number ans = 0;
    for(int i = 0; i < left.size; i++)
    {
        ans += left.data[i] * right.data[i];
    }
    return ans;
}
// Pseudovector operator* (const Vector& left, const Vector& right) // exterior product
// Matrix operator* (const Vector& left, const Vector& right) // outer product

bool operator== (const Matrix& left, const Matrix& right)
{
    if(left.rows != right.rows || left.cols != right.cols)
        return false;
    for(int i = 0; i < right.rows; i++) 
        for(int j = 0; j < right.cols; j++)
            if(right.data[i][j] != left.data[i][j])
                return false;
    return true;
}

Matrix operator+ (const Matrix& left, const Matrix& right)
{
    // check size of two matrix
    if (!(left.rows == right.rows && left.cols == right.cols)) 
    {
        std::cout << "Error: matrices are not the same size, cannot add.\n";
        PrintSadCat();
        assert(false);
    }
    // adding
    Matrix ans(left.rows, left.cols);
    for(int i = 0; i < ans.rows; i++) 
        for(int j = 0; j < ans.cols; j++)
            ans.data[i][j] = left.data[i][j] + right.data[i][j];
    return ans;
}

Matrix operator- (const Matrix& left, const Matrix& right)
{
    // check size of two matrix
    if (!(left.rows == right.rows && left.cols == right.cols)) 
    {
        std::cout << "Error: matrices are not the same size, cannot minus.\n";
        PrintSadCat();
        assert(false);
    }
    // minusing
    Matrix ans(left.rows, left.cols);
    for(int i = 0; i < ans.rows; i++) 
        for(int j = 0; j < ans.cols; j++)
            ans.data[i][j] = left.data[i][j] - right.data[i][j];
    return ans;
}

Matrix operator* (const int num, const Matrix& right)
{
    Matrix ans(right.rows, right.cols);
    for(int i = 0; i < ans.rows; i++) 
        for(int j = 0; j < ans.cols; j++)
            ans.data[i][j] = num * right.data[i][j];
    return ans;
}
// reserved for chaing double to fraction, right now Number == double
// Matrix operator* (const Number num, const Matrix& right)
// {
// }

Matrix operator* (const double num, const Matrix& right)
{
    Matrix ans(right.rows, right.cols);
    for(int i = 0; i < ans.rows; i++) 
        for(int j = 0; j < ans.cols; j++)
            ans.data[i][j] = num * right.data[i][j];
    return ans;
}

Matrix operator* (const Matrix& left, const Matrix& right)
{
    if (left.cols != right.rows)
        {
            std::cout << "\nError: the size of two matrix cannot multiply.\n";
            PrintSadCat();
            assert(false);
        }
        // multiplication
        Matrix ans(left.rows, right.cols);
        for(int i = 0; i < left.rows; i++)
            for(int j = 0; j < right.cols; j++)
                ans.data[i][j] = left.RowOfMatrix(i) * right.ColumnOfMatrix(j);
    return ans;
}

Matrix operator* (const Matrix& left, const Vector& right) // we assume here the right vector is a column vector not a row vector
{
    Matrix RIGHT(right.size, 1);
    for(int i = 0; i < right.size; i++)
        RIGHT.data[i][0] = right.data[i];
    Matrix ans = left * RIGHT;
    return ans;
}

Matrix Transpose(const Matrix& A)
{
    Matrix ans(A.cols,A.rows);
    for(int i = 0; i < A.rows; i++)
        for(int j = 0; j < A.cols; j++)
            ans.data[j][i] = A.data[i][j];
    return ans;
}

Matrix Inverse(const Matrix& A) // relied on row reduction, for larger matrix, LU decomposition will be better, but not start yet
{
    if(A.cols != A.rows)// if not square
    {
        std::cout<<"Error: only squares have inverse matrix, if you want find a left/right inverse, ask Emma";
        PrintSadCat();
        assert(false);
    }
    Matrix ans(A.cols, A.cols); // the num of row and column should be same
    if(A.cols == 1)// if 1*1
    {
        ans = A;
        return A;
    }
    if(A.cols == 2)// if 2*2
    {
        
        Number temp = 1 / (A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0]);
        ans.data[0][0] = A.data[1][1];
        ans.data[1][0] = -1 * A.data[1][0];
        ans.data[0][1] = -1 * A.data[0][1];
        ans.data[1][1] = A.data[0][0];
        ans = temp * ans;
        return ans;
    }
    // lets calculate it seriously, if calculated its rank before, then judge is it invertible
    if(A.rank > -1 && A.rank < A.cols)
    {
        std::cout<<"Error: Square A is singular..., it should gives you a pesudo-inverse or any other things here, but i haven't learn yet";
        PrintSadCat();
        assert(false);
    }
    Matrix I(A.cols);// creat a augmented matrix [A|I]
    I = CombineMatrix(A, I, 'H');
    I.RREF();// elementary row operation
    if(I.rank != I.rows)
    {
        std::cout<<"Error: Square A is singular..., it should gives you a pesudo-inverse or any other things here, but i haven't learn yet";
        PrintSadCat();
        assert(false);
    }
    for(int i = I.rows - 1; i > 0; i--)
        for(int temp_i = i - 1; temp_i >= 0; temp_i--)
            I.RowOperation_AddOneRowToAnother(temp_i, i, -1 * I.data[temp_i][i]);
    for(int i = 0; i < ans.cols; i++)
        for(int j = 0; j< ans.cols; j++)
            ans.data[i][j] = I.data[i][j + ans.cols];
    ans.rank = I.rank;
    ans.PositionOfPivot = I.PositionOfPivot;
    return ans;
}

Matrix CombineMatrix(const Matrix& left, const Matrix& right, char direction)
{
    if(direction == 'H')
    {
        if(left.rows == right.rows)
        {
            Matrix A(left.rows, left.cols + right.cols);
            for(int i = 0; i < left.rows; i++)
            {
                for(int j = 0; j < left.cols; j++)
                    A.data[i][j] = left.data[i][j];
                for(int j = 0; j < right.cols; j++)
                    A.data[i][j + left.cols] = right.data[i][j];
            }
            return A;
        }
        else
        {
            std::cout<<"Error: the size of two matrix cannot combine together";
            PrintSadCat();
            assert(false);
        }
    }
    else if(direction == 'V')
    {
        if(left.cols == right.cols)
        {
            Matrix A(left.rows + right.rows, left.cols);
            for(int j = 0; j < left.cols; j++)
            {
                for(int i = 0; i < left.rows; i++)
                    A.data[i][j] = left.data[i][j];
                for(int i = 0; i < right.rows; i++)
                    A.data[i + left.rows][j] = right.data[i][j];
            }
            return A;
        }
        else
        {
            std::cout<<"Error: the size of two matrix cannot combine together";
            PrintSadCat();
            assert(false);
        }
    }
    else
    {
        std::cout<<"Error: unknown error, ask Emma";
        PrintSadCat();
        assert(false);
    }
}

Matrix CombineMatrix(const Matrix& left, const Vector& right, char direction, char position)
{
    if(direction == 'H')
    {
        if(left.rows == right.size)
        {
            if(position == 'F')
            {
                Matrix A(left.rows, left.cols + 1);
                for(int i = 0; i < left.rows; i++)
                {
                    for(int j = 1; j < left.cols + 1; j++)
                        A.data[i][j] = left.data[i][j - 1];              
                    A.data[i][0] = right.data[i];
                }
                return A;
            }
            else if(position == 'B')
            {
                Matrix A(left.rows, left.cols + 1);
                for(int i = 0; i < left.rows; i++)
                {
                    for(int j = 0; j < left.cols; j++)
                        A.data[i][j] = left.data[i][j];              
                    A.data[i][left.cols] = right.data[i];
                }
                return A;
            }
        }  
    }
    else if(direction == 'V')
    {
        if(left.cols == right.size)
        {
            if(position == 'F')
            {
                Matrix A(left.rows + 1, left.cols);
                for(int j = 0; j < left.cols; j++)
                {
                    for(int i = 1; i < left.rows + 1; i++)
                        A.data[i][j] = left.data[i - 1][j];              
                    A.data[0][j] = right.data[j];
                }
                return A;
            }
            else if(position == 'B')
            {
                Matrix A(left.rows + 1, left.cols);
                for(int j = 0; j < left.cols; j++)
                {
                    for(int i = 0; i < left.rows; i++)
                        A.data[i][j] = left.data[i][j];              
                    A.data[left.rows][j] = right.data[j];
                }
                return A;
            }
        }  
    }
    std::cout<<"Error: unknown error, ask Emma";
    PrintSadCat();
    assert(false);
}

solutionOfLinearEquation::solutionOfLinearEquation()
{
    ifSolution = false;
    ifUniqueSolution = false;
    numOfFreeVaraible = 0;
    Matrix Solution;
}

solutionOfLinearEquation::~solutionOfLinearEquation()
{
    // yes, nothing here, if you believe it is empty, you can draw a cute kitty.
}

void solutionOfLinearEquation::print()
{
    std::cout << "the linear equations";
    if(ifSolution == false)
    {
        std::cout << " doesn't have solutions (why not uses least square method to find a optimal solution ?)"; // plans using Least Squares Method to find approximate solutions
        return;
    }
    if(ifUniqueSolution == true)
    {
        std::cout << " have a unique set of solutions: \n";
        for(int i = 0; i < solution.rows; i++)
            std::cout << "x" << i+1 << " = "<< solution.data[i][0] << std::endl;
        return;
    }
    std::cout << " have infinite solutions with " << numOfFreeVaraible << " free varaible: \n(sorry its hard to display it on the terminal, so I only can give an Latex form)\n" << R"(\begin{bmatrix})";
    for(int i = 0; i < solution.rows; i++)
        std::cout << "x_{" << i+1 << R"(}\\)";
    std::cout << R"(\end{bmatrix}=\begin{bmatrix})";
    for(int i = 0; i < solution.rows; i++)
        std::cout << solution.data[i][0] << R"(\\)";
    std::cout << R"(\end{bmatrix})";
    for(int j = 1; j < solution.cols; j++)
    {
        std::cout << R"(+\begin{bmatrix})";
        for(int i = 0; i < solution.rows; i++)
            std::cout << solution.data[i][j] << R"(\\)";
        std::cout << R"(\end{bmatrix}c_{)" << j << "}";
    }
    std::cout<<"\n";
    PrintCat();
}

solutionOfLinearEquation& solutionOfLinearEquation::operator=(const solutionOfLinearEquation& right)
{
    if(this != &right)
    {
        // create new memory
        ifSolution = right.ifSolution;
        ifUniqueSolution = right.ifUniqueSolution;
        solution = right.solution;
        numOfFreeVaraible = right.numOfFreeVaraible;
    }
    return *this;
}

const inline bool solutionOfLinearEquation::getIfSolution()
{
    if(ifSolution == true)
        return true;
    return false;
}

const inline bool solutionOfLinearEquation::getIfUniqueSolution()
{
    if(ifUniqueSolution == true)
        return true;
    return false;
}

solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b)
{
    if(A.rows != b.size)
    {
        std::cout<<"Error: unknown error, ask Emma";
        PrintSadCat();
        assert(false);
    }
    solutionOfLinearEquation x;
    Matrix Augment = CombineMatrix(A, b, 'H', 'B');
    // Gaussian Elimination
    Augment.RREF();
    // no solution
    for(int i = Augment.rows - 1; i >= 0; i--)
    {
        if(Augment.data[i][Augment.cols - 1] == 0)
            continue;
        if(Augment.data[i][Augment.cols - 2] == 0)
            return x;
        else
            break;
    }
    x.ifSolution = true;
    // unique solutions
    if(Augment.rank == (Augment.cols - 1))
        x.ifUniqueSolution = true;
    else
    {
        // if coefficient matrix is not square, make it square
        if(Augment.rows < (Augment.cols - 1))
        {
            int temp_rank = Augment.rank;
            Vector temp_pivot(Augment.cols);
            temp_pivot = Augment.PositionOfPivot;
            Matrix temp(Augment.cols - Augment.rows - 1,Augment.cols);
            temp.fill(0);
            Augment = CombineMatrix(Augment, temp, 'V');
            Augment.rank = temp_rank;
            Augment.PositionOfPivot = temp_pivot;
        }
    }
    // solve x
    Matrix ans(Augment.rows, Augment.rows - Augment.rank + 1); 
    ans.fill(0);
    for(int i = 0; i < Augment.rows; i++) // let vector b be the first column, waiting to be minus
        ans.data[i][0] = Augment.data[i][Augment.cols - 1];
    for(int i = Augment.rows - 1; i >= 0; i--) // Augmented matrix' num of row should one less than column
    {
        if(Augment.PositionOfPivot.data[i] == 0) // not pivot, means x_{j} is a free varaible
        {
            x.numOfFreeVaraible++;
            for(int j = 0; j < Augment.rows - Augment.rank + 1; j++)
            {
                if(j == x.numOfFreeVaraible)
                    ans.data[i][j] = 1;
                else
                    ans.data[i][j] = 0;
            }
        }
        else
        {
            for(int temp_i = i + 1; temp_i < Augment.rows; temp_i++)
            {
                for( int j = 0; j <= x.numOfFreeVaraible; j++)
                    ans.data[i][j] -= Augment.data[i][temp_i] * ans.data[temp_i][j];
            }
        }
    }
    ans.ErrorToZero();
    x.solution = ans;
    if(x.numOfFreeVaraible != Augment.rows - Augment.rank)
    {
        std::cout << "(rank - row) is:" << Augment.rows - Augment.rank << "\n number of free varaibles" << x.numOfFreeVaraible;
        PrintSadCat();
        std::cout << "we meet a small problem, all four engine are off\n";
        Augment.printALLinfo();
        x.print();
        assert(false);
    }
    return x;
}

Matrix leastSquareMethod(const Matrix& x, const Vector& y) // (m is the num of observations, while n is num of variables (= 1 + num of independent variables)) X is m*(n-1) matrix of observation value of independent variables(means you don't need to add the column of 1 for constant when inputing), and Y is m*1 Vector of observation value of response variables. (right now is focused on only one response variable and using a linear function for regression)
{
    Matrix temp(x.rows, 1); // 
    temp.fill(1);
    Matrix X = CombineMatrix(x, temp, 'H');
    Matrix ans = Inverse(Transpose(X) * X) * (Transpose(X) * y);
    return ans;
}

Matrix leastSquareMethod(Vector& x, const Vector& y) // (m is the num of observations, while n=2 is num of variables (= 1 + num of independent variables)) X is m*(n-1) matrix of observation value of independent variables(means you don't need to add the column of 1 for constant when inputing), and Y is m*1 Vector of observation value of response variables. (right now is focused on only one response variable and using a linear function for regression)
{
    Matrix temp(x.getSize(), 1);
    temp.fill(1);
    Matrix X = CombineMatrix(temp, x, 'H', 'F');
    Matrix ans = Inverse(Transpose(X) * X) * (Transpose(X) * y);
    return ans;
}