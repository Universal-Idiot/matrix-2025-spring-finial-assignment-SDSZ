#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <cassert> // provide "assert(false);"function, stop the program when met a error
#include <iomanip> // provide "std::fixed" and "std::setprecision(digit)" function
#include <fstream> // file_stream
#include <unistd.h> // provide "readlink" function
#include <libgen.h> // provide "dirname" function

#define Number double // reserved for chaing double to fraction

// draw kitty cat, treasure of this project
static inline void PrintHappyCat() 
{
    std::cout<<'\n'<<" Λ___Λ\n| ^  ^|\n|  v  |\n|     |\n";
}
static inline void PrintSadCat(std::string ss_ss_ss)
{
    std::cout << "\nError: " << ss_ss_ss;
    std::cout<<'\n'<<" Λ___Λ\n| T  T|\n|  _  |\n|     |\n";
    assert(false);
}
static inline void PrintCat()
{
    std::cout<<'\n'<<" Λ___Λ\n| η  η|\n|  μ  |\n|     |\n";
}

class Matrix;
class solutionOfLinearEquation;
class Vector;
class fraction;

const double epsilon = 1e-13;
long long int GCD(long long int a, long long int b);

class fraction // not start yet & well i believe i need to learn how to use template, since this class is different from other, aiming to replace double in this whole program
{
    private:
        long long int numerator; // denominator is usually positive, possitive or negative sign of this fraction will storing in numerator
        long long int denominator; // denominator will never be 0 !!!

    public:
        // constructor
        fraction();
        fraction(long long int n, long long int d);
        fraction(const fraction& right);
        fraction(const long long int right);

        // destructor
        ~fraction();

        // member function
        void impart();
        void print(); // in form of a/b
        void printInLatex(); // in form of \frac{a}{b}
        long long int getNumerator();
        long long int getDenominator();
        void simplification();
        void intToFration(int a);
        void doubleToFration(double a);
        double fractionToDouble();

        // operator overloading
        fraction& operator=(const fraction& right);
        fraction& operator=(const long long int& right);

        //friend
        friend fraction operator+ (const fraction& left, const fraction& right);
        friend fraction operator+ (const fraction& left, const int& right);
        friend fraction operator- (const fraction& left, const fraction& right);
        friend fraction operator* (const fraction& left, const fraction& right);
        friend fraction operator* (const int& left, const fraction& right);
        friend fraction operator/ (const fraction& left, const fraction& right);
        friend fraction operator/ (const int& left, const fraction& right);
        friend bool operator== (const fraction& left, const fraction& right);
        friend bool operator== (const fraction& left, const int& right);
        friend bool operator== (const fraction& left, const double& right);
        friend bool operator!= (const fraction& left, const fraction& right);
        friend bool operator!= (const fraction& left, const int& right);
        friend bool operator> (const fraction& left, const fraction& right);
        friend bool operator< (const fraction& left, const fraction& right);
        friend bool operator>= (const fraction& left, const fraction& right);
        friend bool operator<= (const fraction& left, const fraction& right);
        friend fraction abs(fraction x);
        friend int fToi(fraction x); //懒，目前只写了，化简之后分母为1的情况
} ;

const fraction epsilon_f(1,1e13);

class Vector //up to now, this class only developed for matrix mulitplcation, have long way to go
{
    private:
        int size;
        Number* data;

    public:
        // constructor
        Vector(int d);
        Vector();

        // destructor
        ~Vector();

        // member function
        void impart();
        void print();
        void fill(Number a);
        Number length(); // not complete
        Number norm(int a); // not complete
        void add(Number a);
        int getSize();
        Number getdata(int i);

        // operator overloading
        Vector& operator=(const Vector& right);

        // friend
        friend class Matrix;
        friend class Matrix_f;
        friend bool operator== (const Vector& left, const Vector& right);
        friend Vector operator* (Number num, const Vector& right);
        friend Number operator* (Vector left, Vector right);
        friend Matrix operator* (const Matrix& left, const Vector& right);
        friend Matrix CombineMatrix(const Matrix& left, const Vector& right, char direction, char position); // H: horizontal; V: vertical;; F: front; B: back;// in 'V', front is on the top, back is at the bottom
        friend solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b);// not test yet
} ;

class Matrix
{
    private: 
        int rows, cols, rank;
        Number** data;
        Vector PositionOfPivot;// 1 means this column have pivot, 0 means this column does not have pivot.
    public:
        // constructor
        Matrix(int r, int c);
        Matrix(int size); // create a n*n identity matrix
        Matrix();
        Matrix(char c); // actually, this constructor function should be "Matrix();", but i have already define that function, and i aren't sure is any other function uses this feature that "Matrix a;" will create a 1*1 matrix
        Matrix(const Matrix& right);
        
        //destroyer
        ~Matrix();

        // member function
        // input & output in io-stream
        void impart(); // impart
        void print();
        void print(int digit); // create a n*n identity matrix
        void printALLinfo();
        int getNumOfColumn();
        int getNumOfrow();
        // initialize 
        void fill(Number a); // fill the matrix with a double
        void ErrorToZero(); // if there is any value like 1e-15 that looks like float error, it will be converted to 0
        // get row & column from matrix
        Vector RowOfMatrix(int Num_r) const;
        Vector ColumnOfMatrix(int Num_c) const;
        Number getData(int r, int c);
        // row operation (the number of row is from 0 to rows-1, consistent with number of array)
        void RowOperation_MultiplyScalar(int Num_r, Number Num);
        void RowOperation_ExchangeRow(int Num_r_1, int Num_r_2);
        void RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, Number Num); // Num_r_1 is the row you are operating, Num_r_2 is the another row you want to add to Num_r_1
        void REF(); // to ROW ECHELON FORM
        // void makeItSquare(int a); // fill the rest of non-square matrix with a, stopped, because it is useless
        int Rank();
        Number Det(); // determiant
        void RREF();

        // operator overloading
        Matrix& operator=(const Matrix& right);// asignment (both "int a = b;" and "int a; a = b;" are deep copy, not shallow copy)

        //friend
        friend class solutionOfLinearEquation;
        friend bool operator== (const Matrix& left, const Matrix& right);
        friend Matrix operator+ (const Matrix& left, const Matrix& right);
        friend Matrix operator- (const Matrix& left, const Matrix& right);
        friend Matrix operator* (const Number num, const Matrix& right);
        // friend Matrix operator* (const double num, const Matrix& right);
        friend Matrix operator* (const int num, const Matrix& right);
        friend Matrix operator* (const Matrix& left, const Matrix& right);
        friend Matrix operator* (const Matrix& left, const Vector& right);
        friend Matrix Transpose(const Matrix& A);
        friend Matrix Inverse(const Matrix& A); // using row reduction, no LU decomposition yet
        friend Matrix CombineMatrix(const Matrix& left, const Matrix& right, char direction);// H: horizontal; V: vertical //with "left" matrix on the top, and "right" matrix at the bottom
        friend Matrix CombineMatrix(const Matrix& left, const Vector& right, char direction, char position); // H: horizontal; V: vertical;; F: front; B: back;// in 'V', front is on the top, back is at the bottom
        friend void LUdecompositionForSquare(); // not start yet
        friend solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b); // using Gaussian Elimination, no LU decomposition
        friend Matrix projectionXYZ(int numOfDimension); // not start yet
        friend Matrix leastSquareMethod(const Matrix& X, const Vector& Y); // (n is the num of observations, while m is num of variables (= 1 + num of independent variables)) X is n*(m-1) matrix of observation value of independent variables(means you don't need to add the column of 1 for constant when inputing), and Y is n*1 Vector of observation value of response variables. (right now is focused on only one response variable and using a linear function for regression)
} ;

class Matrix_f
{
    private:
        int rows, cols, rank;
        fraction** data;
        Vector PositionOfPivot;// 1 means this column have pivot, 0 means this column does not have pivot.
    public:
        // constructor
        Matrix_f(int r, int c);
        Matrix_f(int size); // create a n*n identity matrix
        Matrix_f();
        Matrix_f(const Matrix_f& other);
        //destroyer
        ~Matrix_f();
        // input & output in io-stream
        void impartInt(); // impart
        void print();
        void printInLatex(); // create a n*n identity matrix
        void printALLinfo();
        // member function
        void writeElements(int r, int c, fraction a);
        fraction getElements(int r, int c);
        int getRows();
        int getCols();
        void REF();
        void RREF();
        void fill(int a);
        void RowOperation_MultiplyScalar(int Num_r, fraction Num); //目前只支持分数
        void RowOperation_ExchangeRow(int Num_r_1, int Num_r_2);
        void RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, fraction Num); // Num_r_1 is the row you are operating, Num_r_2 is the another row you want to add to Num_r_1
        void ColumnOperation_MultiplyScalar(int Num_c, long long int Num); //目前只支持整数
        Vector RowOfMatrix(int Num_r) const;
        void clearTheDenominator(int start_c, int end_c); // clear denominators in columns, by multiple an integer to each row of one column. perticularly used on the solution of linear equations, since i storing those by columns not by rows, and the first column is constant which cannot excecute scalar mutilplication
        void deleteOneLastRow(); // 懒，所以，positionOfPivot根本就没拷贝
        // operator overloading
        Matrix_f& operator=(const Matrix_f& right);
        // friend
        friend Matrix_f CombineMatrix(const Matrix_f& left, const Matrix_f& right, char direction);// H: horizontal; V: vertical //with "left" matrix on the top, and "right" matrix at the bottom
        friend Matrix_f SolveLinearEquationAndPrint(const Matrix_f& A, const Matrix_f& b);
        friend Matrix_f operator* (const int num, const Matrix_f& right);
} ;

class solutionOfLinearEquation
{
    private:
        bool ifSolution;
        bool ifUniqueSolution;
        int numOfFreeVaraible;
        Matrix solution;

    public:
        // constructor
        solutionOfLinearEquation();

        // destructor
        ~solutionOfLinearEquation();

        // member function
        void print();
        const inline bool getIfSolution(); // not test yet
        const inline bool getIfUniqueSolution(); // not test yet

        // operator overloading
        solutionOfLinearEquation& operator=(const solutionOfLinearEquation& right); // not test yet

        // friend
        friend solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b); // not test yet// using Gaussian Elimination, no LU decomposition
} ;

Matrix leastSquareMethod(Vector& x, Vector& y);

#endif