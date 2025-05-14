#include <iostream>
#include <cmath>

const double epsilon = 1e-15;
using namespace std;

int main()
{
    //declearation of functions
    void PrintMatrix(double** data, int rows, int cols);
    void InputMatrix(double** data, int rows, int cols);
    double DotProductOfVector(double* v1, double* v2, int length);

while(1){
    bool If_linear_independent = true;
    //enter rows & cols
    int rows, cols;
    cout << "Please enter number of rows & columns(yes, please enter the set of vector in matrix form, every column is a vector): \n";
    cin >> rows >> cols;

    //A - 动态分配
    double **A = new double*[rows];
    for(int i = 0; i < rows; i++)
        A[i] = new double[cols];
    //V - 动态分配
    double **V = new double*[rows];
    for(int i = 0; i < rows; i++)
        V[i] = new double[cols];
    //动态分配两个向量
    double* x = new double[rows];
    double* v = new double[rows];

    //enter matrix
    cout << "Please enter the matirx";
    InputMatrix(A, rows, cols);

    //vn=xn
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++) 
            V[i][j] = A[i][j];

    //Gram-Schmidt Process
    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
            x[j] = A[j][i];

        //vn=xn-c1x1-c2x2-...-cn-1xn-1
        for(int j = 0; j < i; j++)
        {
            double temp = 0;
            for(int k = 0; k < rows; k++)       
                v[k] = V[k][j];  

            double c = DotProductOfVector(x, v, rows) / DotProductOfVector(v, v, rows);

            for(int k = 0; k < rows; k++)
            {
                V[k][i] -= c * V[k][j];
                temp += V[k][i];
            }
            if(abs(temp) < epsilon)
                If_linear_independent = false;
        }
    }

    //0
    for(int i =0; i < rows; i++)
        for(int j=0; j < cols; j++)
            if(abs(V[i][j]) < epsilon)
                V[i][j] = 0;

    //unify
    for(int i = 0; i < cols; i++)
    {
        //mode
        double mode = 0;
        for(int j = 0; j < rows; j++)
            mode += V[j][i] * V[j][i];
        mode = sqrt(mode);

        for(int j = 0; j < rows; j++)
            if(mode > epsilon)
                V[j][i] = V[j][i] / mode;
    }

    //if_linear_independent
    if(cols > rows)
    {
        If_linear_independent = false;
        for(int i = rows; i < cols; i++)
            for(int j = 0; j < rows; j++)
                V[j][i] = 0;
    }

    //print
    cout<<"\n\northogoal basis is:\n";
    if(If_linear_independent == false)
        cout<<"(WARNING: the set of vector is LINEAR DEPENDENT)\n";
    else
        PrintMatrix(V, rows, cols);
    
    //A - 释放内存
    for(int i = 0; i < rows; i++)
    delete[] A[i];
    delete[] A;
    //V - 释放内存
    for(int i = 0; i < rows; i++)
    delete[] V[i];
    delete[] V;
    //向量释放内存
    delete[] x;
    delete[] v;
}
    return 0;
}

void PrintMatrix(double** data, int rows, int cols)
{
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++)
        {
            cout << data[i][j] << ' ';
        }
        cout << '\n';
    }
}

void InputMatrix(double** data, int rows, int cols)
{
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
             cin >> data[i][j];
}

double DotProductOfVector(double* v1, double* v2, int length)
{
    double ans = 0;
    for(int i = 0; i < length; i++)
    {
        ans += v1[i] * v2[i];
    }
    return ans;
}