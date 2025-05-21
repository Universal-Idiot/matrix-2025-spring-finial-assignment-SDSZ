#include "matrix.hpp"

// matrix.cpp
// Implementation of Linear Algebra classes
// Author: 11767（文俊钦）
// Date: 2025-5-14
// 哦天哪还没写多少呢已经成一坨屎山了……而且一些东西还是AI现教我的。

long long int GCD(long long int a, long long int b)
{
    if(a != 0 && b != 0)
    {
        if(a%b == 0)
            return b;
        else 
            return GCD(b, a%b);
    }
	return 1;
}

fraction::fraction() //默认是分子为0分母为1的零
{
    denominator = 1;
    numerator = 0;
}

fraction::fraction(long long int n, long long int d) : numerator(n), denominator(d)
{
    if(denominator == 0)
        PrintSadCat("denominator should never be ZERO");
    if(denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
    simplification();
}

fraction::fraction(const fraction& right)
{
    numerator = right.numerator;
    denominator = right.denominator;
    simplification();
}

fraction::fraction(const long long int right)
{
	numerator = right;
    denominator = 1;
    simplification();
}

fraction::~fraction()
{
    // yes, nothing here, really
}

void fraction::print() // in form of a/b
{
    if(numerator == 0)
        std::cout << 0;
    else if(denominator == 1)
        std::cout << numerator;
    else
		std::cout << numerator << '/' << denominator;
}

void fraction::printInLatex() // in form of \frac{a}{b}
{
    if(numerator == 0)
        std::cout << 0;
    else if(denominator == 1)
        std::cout << numerator;
	else
    	std::cout << R"(\frac{)" << numerator << "}{" << denominator << '}';
}

long long int fraction::getNumerator()
{
    return numerator;
}

long long int fraction::getDenominator()
{
    return denominator;
}

void fraction::simplification()
{
    int gcd = GCD(denominator, numerator);
    denominator /= gcd;
    numerator /= gcd;
	if(denominator == 0)
		PrintSadCat("simplification: denominator should never be ZERO");
	if(denominator < 0)
	{
		denominator *= -1;
		numerator *= -1;
	}
}

fraction abs(fraction x)
{
    if(x.denominator != 0 && x.numerator < 0)
        return -1 * x;
	else return x;
}

fraction& fraction::operator=(const fraction& right)
{
    if(this != &right)
    {
        numerator = right.numerator;
        denominator = right.denominator;
    }
    return *this;
}

fraction& fraction::operator=(const long long int& right)
{
    numerator = right;
    denominator = 1;
	return *this;
}

fraction operator+ (const fraction& left, const fraction& right)
{
    fraction ans;
    int gcd = GCD(left.denominator, right.denominator);
    ans.denominator = left.denominator * right.denominator / gcd;
    ans.numerator = (left.numerator * (ans.denominator / left.denominator)) + (right.numerator * (ans.denominator / right.denominator));
    ans.simplification();
    return ans;
}

fraction operator+ (const fraction& left, const int& right)
{
    fraction ans = left;
    ans.numerator += right * ans.denominator;
    ans.simplification();
    return ans;
}

fraction operator- (const fraction& left, const fraction& right)
{
    fraction ans;
    int gcd = GCD(left.denominator, right.denominator);
    ans.denominator = left.denominator * right.denominator / gcd;
    ans.numerator = (left.numerator * (ans.denominator / left.denominator)) - (right.numerator * (ans.denominator / right.denominator));
    ans.simplification();
    return ans;
}

fraction operator* (const fraction& left, const fraction& right)
{
    fraction ans;
    ans.denominator = left.denominator * right.denominator;
    ans.numerator = left.numerator * right.numerator;
    ans.simplification();
    return ans;
}

fraction operator* (const int& left, const fraction& right)
{
    fraction ans;
    ans.denominator = right.denominator;
    ans.numerator = left * right.numerator;
    ans.simplification();
    return ans;
}

fraction operator/ (const fraction& left, const fraction& right)
{
    if(right.numerator != 0) {
        fraction ans;
        ans.denominator = left.denominator * right.numerator;
        ans.numerator = left.numerator * right.denominator;
        ans.simplification();
        return ans;
    }
    else
        PrintSadCat("denominator should never be ZERO");
	return 0;
}

fraction operator/ (const int& left, const fraction& right)
{
    fraction ans;
    ans.denominator = right.numerator;
    ans.numerator = left * right.denominator;
	ans.simplification();
    return ans;
}

bool operator== (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
    if(ans.numerator == 0)
        return true;
    else
        return false;
}

bool operator== (const fraction& left, const int& right)
{
    if(left.numerator == (left.denominator * right))
        return true;
    else
        return false;
}

bool operator== (const fraction& left, const double& right); // not start yet

bool operator!= (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
    if(ans.numerator == 0)
        return false;
    else
        return true;
}

bool operator!= (const fraction& left, const int& right)
{
    fraction ans = left + (-1 * right);
    if(ans.numerator == 0)
        return false;
    else
        return true;
}

bool operator> (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
	if(ans.denominator < 0)
	{
		ans.denominator *= -1;
		ans.numerator *= -1;
	}
    if(ans.numerator > 0)
        return true;
    else
        return false;
}

bool operator< (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
	if(ans.denominator < 0)
	{
		ans.denominator *= -1;
		ans.numerator *= -1;
	}
    if(ans.numerator < 0)
        return true;
    else
        return false;
}

bool operator>= (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
    if(ans.numerator >= 0)
        return true;
    else
        return false;
}

bool operator<= (const fraction& left, const fraction& right)
{
    fraction ans = left - right;
    if(ans.numerator <= 0)
        return true;
    else
        return false;
}

int fToi(fraction x)
{
    x.simplification();
    if(x.getDenominator() == 1)
        return x.getNumerator();
    return 0;
}

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
    size = 0; // 原来是赋值为1，改成了赋值为零，不知道会不会导致什么bug
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

Number Vector::getdata(int i)
{
	return data[i];
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
        PrintSadCat("");
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
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
    for(int i = 0; i < cols; i++)
        data[Num_r][i] = Num * data[Num_r][i];
}

void Matrix::RowOperation_ExchangeRow(int Num_r_1, int Num_r_2)
{
    if(Num_r_1 == Num_r_2)
        return;
    if (Num_r_1 < 0 || Num_r_1 >= rows || Num_r_2 < 0 || Num_r_2 >= rows) 
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
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
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
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
        PrintSadCat("only square have determiant");
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
        PrintSadCat("Unknown error, ask Emma");
	return 0;
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
			if(PositionOfPivot.data)
				delete[] data;
            PositionOfPivot.data = new Number[cols];
            for(int i = 0; i < cols; i++)
                PositionOfPivot.data[i] = right.PositionOfPivot.data[i];
        }
		else
			PositionOfPivot.data = nullptr;
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
        PrintSadCat("");
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
        PrintSadCat("matrice are not same size, cannot add.");
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
        PrintSadCat("matrices are not the same size, cannot minus.");
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
        PrintSadCat("the size of two matrix cannot multuply");
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
        PrintSadCat("only squares have inverse matrix, if you want find a left/right inverse, ask Emma");
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
        PrintSadCat("Square A is singular..., it should gives you a pesudo-inverse or any other things here, but i haven't learn yet");
    Matrix I(A.cols);// creat a augmented matrix [A|I]
    I = CombineMatrix(A, I, 'H');
    I.RREF();// elementary row operation
    if(I.rank != I.rows)
        PrintSadCat("Square A is singular..., it should gives you a pesudo-inverse or any other things here, but i haven't learn yet");
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
            PrintSadCat("the size of two matrix cannot combine together");
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
            PrintSadCat("the size of two matrix cannot combine together");
    }
    else
        PrintSadCat("two matrix cannot combine together");
	return 0;
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
    PrintSadCat("unknown error");
	return 0;
}

Matrix_f:: Matrix_f(int r, int c) : rows(r), cols(c), rank(-1)
{
    if(rows <= 0 || cols <= 0)
    {
        PrintSadCat(" Matrix_f(int r, int c): number of columns and rows should be positive integers");
    }
    data = new fraction*[rows];
    for(int i = 0; i < rows; i++)
        data[i] = new fraction[cols];
    PositionOfPivot.data = nullptr;
}

Matrix_f:: Matrix_f(int size) : rows(size), cols(size), rank(-1)
{
    data = new fraction*[rows];
    for(int i = 0; i < rows; i++)
    {
        data[i] = new fraction[cols];
        for(int j = 0; j < cols; j++)
            if(i == j) data[i][j] = 1;
            else data[i][j] = 0;
    }
    PositionOfPivot.data = nullptr;
}

Matrix_f::Matrix_f() : rows(0), cols(0), rank(-1) 
{
    data = nullptr;
    PositionOfPivot.data = nullptr;
}

Matrix_f::~Matrix_f()
{
    if(data)
    {
        for(int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }
    // class vector have a destroyer function
}

Matrix_f::Matrix_f(const Matrix_f& other) { // 这风格一看就不是我写的，啊确实不是，GPT帮我改的，谢谢它，要不我真的急的要砸屏幕了
    rows = other.rows;
    cols = other.cols;
    rank = other.rank;
    // 深拷贝 data
    data = new fraction*[rows];
    for(int i = 0; i < rows; i++) {
        data[i] = new fraction[cols];
        for(int j = 0; j < cols; j++)
            data[i][j] = other.data[i][j];
    }
    // 深拷贝 PositionOfPivot
    if(other.PositionOfPivot.data) {
        PositionOfPivot.data = new Number[cols];
        for(int i = 0; i < cols; i++)
            PositionOfPivot.data[i] = other.PositionOfPivot.data[i];
        PositionOfPivot.size = other.PositionOfPivot.size;
    } else {
        PositionOfPivot.data = nullptr;
        PositionOfPivot.size = 0;
    }
}

void Matrix_f::impartInt() // impart
{
    int x;
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
        {
            std::cin >> x;
            data[i][j] = x;
        }
}

void Matrix_f::print()
{
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            data[i][j].print();
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void Matrix_f::printInLatex()
{
    std::cout << R"(\begin{bmatrix})";
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            data[i][j].printInLatex();
            if(j == cols - 1)
			{
				if (i == rows - 1)
                	break;
				else
					std::cout << R"(\\)";
			}
            else
                std::cout << '&';
        }
    }
    std::cout << R"(\end{bmatrix})";
}

void Matrix_f::printALLinfo()
{
    std::cout << "\n\nrows: " << rows << "\ncolumns: " << cols;
    std::cout << "\nthe matrix is: \n";
    printInLatex();
    std::cout << '\n' << "rank: ";
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

void Matrix_f::writeElements(int r, int c, fraction a)
{
	if(r >=0 && r < rows && c >= 0 && c < cols)
		data[r][c] = a;
	else{//test
        std::cout<<"\n\nerror, r: "<<r <<", c: "<<c<<", a: ";
        a.print();
		PrintSadCat("writeElements: r and c are out of size of matrix, please check again");
    }
}

fraction Matrix_f::getElements(int r, int c)
{
	fraction ans;
	if(r >=0 && r < rows && c>=0 && c<cols)
		ans = data[r][c];
	else{//test
        std::cout<<"\n\nerror, r: "<<r <<", c: "<<c<<" \n";
		PrintSadCat("getElements r and c are out of size of matrix, please check again");
    }
	return ans;
}

 int Matrix_f::getRows()
 {
    return rows;
 }

 int Matrix_f::getCols()
 {
    return cols;
 }

void Matrix_f::RowOperation_MultiplyScalar(int Num_r, fraction Num)
{
    if (Num_r < 0 || Num_r >= rows)
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
    for(int i = 0; i < cols; i++)
        data[Num_r][i] = Num * data[Num_r][i];
}

void Matrix_f::RowOperation_ExchangeRow(int Num_r_1, int Num_r_2)
{
    if(Num_r_1 == Num_r_2)
        return;
    if (Num_r_1 < 0 || Num_r_1 >= rows || Num_r_2 < 0 || Num_r_2 >= rows) 
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
    // storing temp
    Matrix_f temp(1, cols);
    for(int i = 0; i < cols; i++)
        temp.data[0][i] = data[Num_r_1][i];
    for(int i = 0; i < cols; i++)
        data[Num_r_1][i] = data[Num_r_2][i];
    for(int i = 0; i < cols; i++)
        data[Num_r_2][i] = temp.data[0][i];
}

void Matrix_f::RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, fraction Num) // Num_r_1 is the row you are operating, Num_r_2 is the another row you want to add to Num_r_1
{
    if (Num_r_1 == Num_r_2 || Num_r_1 < 0 || Num_r_1 >= rows || Num_r_2 < 0 || Num_r_2 >= rows) 
        PrintSadCat("the number of rows is NOT applicable to excecute an expected row operation.");
    for(int i = 0; i < cols; i++)
        data[Num_r_1][i] = data[Num_r_1][i] + Num * data[Num_r_2][i];
}

void Matrix_f::ColumnOperation_MultiplyScalar(int Num_c, long long int Num) //目前只支持整数
{
	if (Num_c < 0 || Num_c >= cols)
        PrintSadCat("the number of rows is NOT applicable to excecute an expected column operation.");
    for(int i = 0; i < rows; i++)
        data[i][Num_c] = Num * data[i][Num_c];
}

void Matrix_f::REF() // to ROW ECHELON FORM
{
    PositionOfPivot.data = new double[cols];
    PositionOfPivot.size = cols;
    rank = 0;
    fraction temp(1, 1); // storing the coefficient
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
            temp = data[i][j] / data[position - 1][j];
            RowOperation_AddOneRowToAnother(i, position - 1, -1 * temp);
        }
        ifLoop = false;
    }
}

void Matrix_f::RREF()
{
    fraction temp;
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
}

void Matrix_f::fill(int a)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
			data[i][j] = a;
}

void Matrix_f::clearTheDenominator(int start_c, int end_c) // end_c = -1 means from start_c to the end of the matrix, clear denominators in columns, by multiple an integer to each row of one column. perticularly used on the solution of linear equations, since i storing those by columns not by rows, and the first column is constant which cannot excecute scalar mutilplication
{
	if(start_c >= 0 && end_c < cols && start_c <= end_c) // end_c should be 1 less than numbor of cols
	{
		for(int j = start_c; j <= end_c; j++)
		{
			for(int i = 0; i < rows; i++)
			{
				if(data[i][j].getDenominator() != 1)
					ColumnOperation_MultiplyScalar(j, data[i][j].getDenominator());
			}
		}
	}
	else if(start_c >= 0 && end_c == -1)
	{
		for(int j = start_c; j < cols; j++)
		{
			for(int i = 0; i < rows; i++)
			{
				if(data[i][j].getDenominator() != 1)
					ColumnOperation_MultiplyScalar(j, data[i][j].getDenominator());
			}
		}
	}
	else
		PrintSadCat("clearTheDenominator: the number of rows is NOT applicable to excecute an expected column operation");
}

void Matrix_f::deleteOneLastRow() // 懒，所以让AI直接帮我改了，快谢谢它
{
    if(data == nullptr || rows == 0)
        return;
    if(rows == 1) {
        for(int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
        data = nullptr;
        rows = 0;
        // PositionOfPivot 也要同步
        if(PositionOfPivot.data) {
            delete[] PositionOfPivot.data;
            PositionOfPivot.data = nullptr;
            PositionOfPivot.size = 0;
        }
        return;
    }
    // 新分配一块更小的内存
    fraction** new_data = new fraction*[rows - 1];
    for(int i = 0; i < rows - 1; i++) {
        new_data[i] = new fraction[cols];
        for(int j = 0; j < cols; j++)
            new_data[i][j] = data[i][j];
    }
    // 释放原有内存
    for(int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
    data = new_data;
    rows--;
    // PositionOfPivot 不变（如果你需要同步处理，也要重新分配）
}

Matrix_f& Matrix_f::operator=(const Matrix_f& right)
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
        data = new fraction*[rows];
        for(int i = 0; i < rows; i++)
        {
            data[i] = new fraction[cols];
            for(int j = 0; j <  cols; j++)
            {
                data[i][j] = right.data[i][j];
            }
        }
        if(right.PositionOfPivot.data)
        {
			if(PositionOfPivot.data)
				delete[] PositionOfPivot.data;
            PositionOfPivot.data = new Number[cols];
            for(int i = 0; i < cols; i++)
                PositionOfPivot.data[i] = right.PositionOfPivot.data[i];
        }
		else
		{
			PositionOfPivot.data = nullptr;
			PositionOfPivot.size = 0;
		}
    }
    return *this;
}

Matrix_f CombineMatrix(const Matrix_f& left, const Matrix_f& right, char direction)
{
	if(left.data == nullptr)
	{
		Matrix_f A = right;
		return A;
	}
	if(right.data == nullptr)
	{
		Matrix_f A = left;
		return A;
	}
    if(direction == 'H')
    {
        if(left.rows == right.rows)
        {
            Matrix_f A(left.rows, left.cols + right.cols);
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
            PrintSadCat("the size of two matrix cannot combine together");
    }
    else if(direction == 'V')
    {
        if(left.cols == right.cols)
        {
            Matrix_f A(left.rows + right.rows, left.cols);
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
            PrintSadCat("the size of two matrix cannot combine together");
    }
    else
        PrintSadCat("Unkown Error, ask Emma");
	return 0;
}

Matrix_f SolveLinearEquationAndPrint(const Matrix_f& A, const Matrix_f& b)
{
    if(A.rows != b.rows)
        PrintSadCat(" why don't you chect the size of two matrix at first?");
    Matrix_f ans, Augment = CombineMatrix(A, b, 'H');
    // Gaussian Elimination
    Augment.RREF();
    // no solution
    for(int i = Augment.rows - 1; i >= 0; i--)
    {
        if(Augment.data[i][Augment.cols - 1] == 0)
            continue;
        if(Augment.data[i][Augment.cols - 2] == 0)
		{
			std::cout<<"linear equations doesn't have solution, you can try least square regression to find a optimal solution";
			return ans; // right now, ans.data = nullptr, which indicate no solution.
		}
        else
            break;
    }
    // does not judge whether have unique solution or infinite, since they both uses n*? matrix to storing, only different in num of columns
	// if coefficient matrix is not square, make it square
	if(Augment.rows < (Augment.cols - 1))
	{
		int temp_rank = Augment.rank;
		Vector temp_pivot(Augment.cols);
		temp_pivot = Augment.PositionOfPivot;
		Matrix_f temp(Augment.cols - Augment.rows - 1, Augment.cols);
		temp.fill(0);
		Augment = CombineMatrix(Augment, temp, 'V');
		Augment.rank = temp_rank;
		Augment.PositionOfPivot = temp_pivot;
	}
    // solve x
    Matrix_f temp(Augment.rows, Augment.rows - Augment.rank + 1);
	ans = temp;
    ans.fill(0);
	int numOfFreeVariable = 0;
    for(int i = 0; i < Augment.rows; i++) // let vector b be the first column, waiting to be minus
        ans.data[i][0] = Augment.data[i][Augment.cols - 1];
    for(int i = Augment.rows - 1; i >= 0; i--) // Augmented matrix' num of row should one less than column
    {
        if(Augment.PositionOfPivot.getdata(i) == 0) // not pivot, means x_{j} is a free varaible
        {
            numOfFreeVariable++;
            for(int j = 0; j < Augment.rows - Augment.rank + 1; j++)
            {
                if(j == numOfFreeVariable)
                    ans.data[i][j] = 1;
                else
                    ans.data[i][j] = 0;
            }
        }
        else
        {
            for(int temp_i = i + 1; temp_i < Augment.rows; temp_i++)
            {
                for( int j = 0; j <= numOfFreeVariable; j++)
                    ans.data[i][j] = ans.data[i][j] - Augment.data[i][temp_i] * ans.data[temp_i][j];
            }
        }
    }
    if(numOfFreeVariable != Augment.rows - Augment.rank)
		PrintSadCat("the num of free variable doesn't equal (cols-rank), we have meet a small problem, all four engine are off");
    return ans;
}

Matrix_f operator* (const int num, const Matrix_f& right)
{
    Matrix_f ans(right.rows, right.cols);
    for(int i = 0; i < ans.rows; i++) 
        for(int j = 0; j < ans.cols; j++)
            ans.data[i][j] = num * right.data[i][j];
    return ans;
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
        PrintSadCat("unknown error");
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
        std::cout << "\n";
        Augment.printALLinfo();
        x.print();
		PrintSadCat("we meet a small problem, all four engine are off");
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