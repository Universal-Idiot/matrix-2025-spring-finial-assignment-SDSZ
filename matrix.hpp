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
        void printInDouble(int digit); // in form of num.numnum
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
        friend fraction abs(const fraction& x);
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
        int rows; // 矩阵的行数
        int cols; // 矩阵的列数
        int rank; // 矩阵的秩；如果未计算则为-1
        double** data; // 用双精度浮点型的指针的指针动态储存矩阵的数据
        Vector PositionOfPivot; // 记录哪列存在主元；第 i+1 个元素为0是此列不存在主元，不等于0是主元在此列的第几行；未计算则 PositionOfPivot.data 为 nullptr

    public:
        // constructor
        Matrix(int r, int c); // 创建一个 r 行 c 列的零矩阵
        Matrix(int size); // 创建一个 size 行 size 列的单位矩阵
        Matrix(); // 创建一个 1 行 1 列的零矩阵
        Matrix(char c); // 创建一个 0 行 0 列的矩阵，不用管c是啥只要有就行，约等于声明一个变量，但是啥也没定义 (ps: 为什么不是上面函数那个干这件事，别问，问就是屎山)
        Matrix(const Matrix& right); // 拷贝构造函数
        
        //destroyer
        ~Matrix();

        // member & friend function
        // // input & output in io-stream
        void impart(); // 从命令行输入，每个元素以空格隔开，什么时候回车并不重要，程序并不知道你要输入多大的矩阵，所以建议你先输入行数和列数，再用第一个构造函数定义变量，然后再用这个输入
        void print(); // 在命令行输出, 
        void print(int digit); // 在命令行里输出，但是每个元素只输出 digit位
        void printALLinfo(); // 输出矩阵的所有信息
        // // operation of object
        int getNumOfColumn(); // 获取行数
        int getNumOfrow(); // 获取列数
        double getData(int r, int c); // 获取第 r+1 行第 c+1 列的元素的值
        Vector RowOfMatrix(int Num_r) const; // 获取第 r+1 行的一整行
        Vector ColumnOfMatrix(int Num_c) const; // 获取第 c+1 列的一整列
        void fill(double a); // 将整个矩阵的每个元素赋值为 a
        void ErrorToZero(); // 消除接近零的浮点数误差：如果矩阵中哪个元素与零的差小于epsilon(=1e-15)，就认为它是零，并赋值为零
        friend Matrix CombineMatrix(const Matrix& left, const Matrix& right, char direction); // 将两个矩阵拼成一个矩阵，最后那个direction有两个取值是有用的：'H'表示H两个矩阵水平拼接，left在左right在右；'V'表示两个矩阵垂直拼接，left在上right在下
        friend Matrix CombineMatrix(const Matrix& left, const Vector& right, char direction, char position); // 将一个矩阵和一个向量拼接成一个矩阵。direction取'H'是矩阵和向量水平拼接；取'V'是竖直拼接。position取'F'是向量在前/上；取'B'是向量在后/下
        // // matrix calculation
        void RowOperation_MultiplyScalar(int Num_r, double Num); // 行操作之数乘一行，将第 Num_r+1 行的每一个元素乘以 Num
        void RowOperation_ExchangeRow(int Num_r_1, int Num_r_2); // 行操作之交换两行
        void RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, double Num); // 行操作之，将第 Num_r_2+1 行的每个元素乘以 Num 加到 第Num_r_1+1 行的每个元素上
        void REF(); // 将矩阵通过行化简操作转换至行梯形矩阵(row echelon form)
        void RREF(); // 
        void RREF_fake(); // 历史遗留问题，我开始以为化简行阶梯矩阵只是把行阶梯矩阵的主元全都变为一，所以搞出了这个怪异的东西，然后后面接着有解方程，那这个形式暂时保留然后构建新的。方法：先调用.REF()，让后将每个主元化成1，先保留吧
        int Rank(); // 计算矩阵的秩，如果行化简过，直接输出成员变量rank的值，如果没有，现场算一下
        double Det(); // 计算此矩阵的行列式，只有方阵才能计算行列式，如果矩阵大于3则用行化简来计算
        friend Matrix Transpose(const Matrix& A); // 计算矩阵的转置，输出一个矩阵（不改变此矩阵）
        friend Matrix Inverse(const Matrix& A); // 计算矩阵的逆（暂时使用行化简，LU分解还没做呢）
        // // operator overloading
        Matrix& operator=(const Matrix& right); // 重载 赋值运算符，深拷贝
        friend bool operator== (const Matrix& left, const Matrix& right); // 重载 等于号
        friend Matrix operator+ (const Matrix& left, const Matrix& right); // 重载 加号
        friend Matrix operator- (const Matrix& left, const Matrix& right); // 重载 减号
        friend Matrix operator* (const double num, const Matrix& right); // 重载 乘号， 一个double的浮点数乘一个矩阵
        friend Matrix operator* (const int num, const Matrix& right); // 重载 乘号，一个int整数乘一个矩阵
        friend Matrix operator* (const Matrix& left, const Matrix& right); // 重载 乘号，一个矩阵乘一个矩阵
        friend Matrix operator* (const Matrix& left, const Vector& right); // 重载 乘号， 一个矩阵乘一个向量，结果理论上是向量，但是一列的矩阵不也一样嘛
        // others
        // friend void LUdecompositionForSquare(); // not start yet
        friend solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b); // using Gaussian Elimination, no LU decomposition
        // friend Matrix projectionXYZ(int numOfDimension); // not start yet
        friend Matrix leastSquareMethod(const Matrix& X, const Vector& Y); // (n is the num of observations, while m is num of variables (= 1 + num of independent variables)) X is n*(m-1) matrix of observation value of independent variables(means you don't need to add the column of 1 for constant when inputing), and Y is n*1 Vector of observation value of response variables. (right now is focused on only one response variable and using a linear function for regression)
        friend class solutionOfLinearEquation;
} ;

class Matrix_f // 每个元素用分数保存的矩阵
{
    private:
        int rows; // 矩阵的行数
        int cols; // 矩阵的列数
        int rank; // 矩阵的秩；如果未计算则为-1
        fraction** data; // 用分数类型的指针的指针动态存储矩阵的数据
        Vector PositionOfPivot; // 记录哪列存在主元；第 i+1 个元素为0是此列不存在主元，不等于0是主元在此列的第几行；未计算则 PositionOfPivot.data 为 nullptr
    public:
        // constructor
        Matrix_f(int r, int c); // 创建一个 r 行 c 列的零矩阵
        Matrix_f(int size); // 创建一个 size 行 size 列的单位矩阵
        Matrix_f(); // 创建一个 0 行 0 列的矩阵，不用管c是啥只要有就行，约等于声明一个变量，但是啥也没定义
        Matrix_f(const Matrix_f& other); // 拷贝构造函数
        //destroyer
        ~Matrix_f();
        // member & friend function
        // // input & output in io-stream
        void impartInt(); // 从命令行以**整数**的形式输入，每个元素以空格隔开，什么时候回车并不重要，程序并不知道你要输入多大的矩阵，所以建议你先输入行数和列数，再用第一个构造函数定义变量，然后再用这个输入
        void print(); // 在命令行输出，除了分母为1输出整数或者分子为0输出0外，每个分数以"a/b"的形式输出
        void printInLatex(); // 在命令行输出，以 Latex 格式
        void printInDouble(int digit); // 在命令行输出，但是每个分数都化成double小数，默认保留两位小数
        void printALLinfo(); // 输出矩阵的所有信息
        // // operation of object
        void writeElements(int r, int c, fraction a); // 给矩阵的第r+1行第c+1列的元素赋予值a
        void writeElements(int r, int c, int a); // 给矩阵的第r+1行第c+1列的元素赋予值a
        fraction getElements(int r, int c); // 获取第r+1行第c+1列的元素的值
        int getRows(); // 获取行数
        int getCols(); // 获取列数
        void fill(fraction a); // 将矩阵里所有的元素赋值为 a
        void fill(int a); // 将矩阵里所有的元素赋值为 a
        friend Matrix_f CombineMatrix(const Matrix_f& left, const Matrix_f& right, char direction);// H: horizontal; V: vertical //with "left" matrix on the top, and "right" matrix at the bottom
        void deleteOneLastRow(); // 删除矩阵的最后一整行 // 懒，所以，positionOfPivot根本就没拷贝
        void clearTheDenominatorByColumn(int start_c, int end_c); // clear denominators from (start_c + 1) column to (end_c + 1) column, by column operations --  multiplying an integer to each rows of one column // perticularly used on the solution of linear equations, since i storing those by columns not by rows, and the first column is constant which cannot excecute scalar mutilplication
        // Matrix Calculation
        void REF();
        void RREF();
        void RREF_fake();
        void RowOperation_MultiplyScalar(int Num_r, fraction Num); // 行操作之数乘一行，将第 Num_r+1 行的每一个元素乘以 Num // 目前只支持分数
        void RowOperation_ExchangeRow(int Num_r_1, int Num_r_2); // 行操作之交换两行
        void RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, fraction Num); // 行操作之，将第 Num_r_2+1 行的每个元素乘以 Num 加到 第Num_r_1+1 行的每个元素上
        void ColumnOperation_MultiplyScalar(int Num_c, long long int Num); // 列操作之数乘一列，目前只支持整数
        // Operator overloading
        Matrix_f& operator=(const Matrix_f& right); // 重载 赋值运算符，深拷贝
        friend Matrix_f operator* (const int num, const Matrix_f& right); // 重载 乘号， 一个整数数乘一个矩阵
        // Others
        friend Matrix_f SolveLinearEquationAndPrint(const Matrix_f& A, const Matrix_f& b);
        
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