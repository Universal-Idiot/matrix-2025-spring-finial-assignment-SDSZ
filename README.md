# *线性代数课期末作业 说明书* 
**by 11767** [点击跳转至Github](https://github.com/Universal-Idiot/matrix-2025-spring-finial-assignment-SDSZ) version: v1.3
___
# 内容
- 内容是用 C++ 实现数学课期末作业，使用面向对象的编程方式，在AI的现学现教的帮助下，将矩阵和向量的运算封装成一个类，所有类和函数的声明放在了```matrix.hpp```中，实现方法放在```matrix.cpp```中，每道题目直接引用封装好的函数就可以了. 
~~*ps: 虽然有AI帮忙，但也算做了这么多，你俩要不请我杯奶茶？*~~ 

- 作业一共四道题目： 
>  1. 编写一段代码，实现 *Gram-Schmidt* 算法. 即首先判断一组输入向量 {a1, a2, · · · , an} 是否线性无关. 若线性相关， 输出该向量组线性相关的结论；若线性无关，输出单位正交的向量组 {q1, q2, · · · , qn}.
> 2. 编写一段代码，配平以下两个化学方程式. 
> *略*
> 3. 编写一段代码，通过 *Gaussian elimination* 实现输入矩阵的 *reduced row echelon form*.
> 4. 编写一段代码，通过最小二乘法实现线性回归.
>> - 给定一组数据 (附件 *data.txt*), 第*1*列为若干城市对应的人口数，第*2*列为在相应城市中开设的便利店的利润，负的利润值表示亏损. 
>> - 基于最小二乘准则，对该数据进行单变量线性回归，并基于回归得到的模型预测当人口数 $x=16$ 时的利润.
___
# 下载 & 运行
- 为了正常地使用和编译，需下载头文件和源文件```matrix.hpp```和```matrix.cpp```，其他```.cpp```文件根据需求下载即可. 然后在 IDE(集成开发环境) 里创建一个项目，将以上文件导入并编译和运行即可. 

- 如果您**没有 IDE**，那还需下载文件`makefile`来同时编译和关联多个文件生成可执行文件。确保您电脑上正确安装了 gcc 和 make, 将您下载的几个文件放在同一个文件夹里，然后打开`makefile`文件，找到一下这一行 (应该是第二行): 

```makefile
file_main = <filename>
```
- 将`<filename>`改为您想要编译的文件的名字 (不带后缀)， 并保存。最后打开命令行输入`make`即可. 

***代码使用了一些C++11及以上的特性，请确保您的编译器符合要求**
___
# 问题
||问题|计划|近期是否打算改|
|:---:|:---:|:---:|:---:|
|1|程序未测试|N/A|N/A|
|2|分数类型的重载太过混乱|使用模板类简化代码|no|
|3|makefile太麻烦|改用cmake|no|
|4|Vector类添加元素时频繁复制删除复制|添加capacity|no|
|5|fraction类和
|6|屎山代码|破作业**how cares**|no|
___
# 计划
|后续计划|（画大饼）|
|:---:|:---:|
|1|继续添加更多功能，例如 LU分解、特征值分解、SVD分解|
|2|学习使用Qt库，添加GUI|
|3|学习模板类，优化代码|
|4|除了完善这个库，还可以开发一些别的功能，比如简单的3D渲染或者解PDE|
___
# 类和函数列表
*敬请期待，喵喵喵喵喵~*
## **1. ```Vector```类**
- 以双精度浮点型储存向量，不要管行向量还是列向量了
- *~~ps：开始做的时候并不知道c++有vector容器，后来才知道但是这个类已经写了，删了岂不浪费了于是就用吧即使容易出问题和低效 :(~~*
- *~~ps: 还有因为开始时很吝啬写成员函数导致声明了一堆友元函数和友元类，就很屎，稍稍损害了类的封装性，虽然后来补上了，但是前面的懒得改了 :(~~*
## **2. ``Matrix``类**
- 以双进度浮点型储存矩阵，并可以进行一些矩阵的运算
*~~ps: 做的时候忘了三五法则导致出了一堆bug...~~*
### 成员变量 (private):
```c++
int rows; // 矩阵的行数
int cols; // 矩阵的列数
int rank; // 矩阵的秩；如果未计算则为-1
double** data; // 用双精度浮点型的指针的指针动态储存矩阵的数据
Vector PositionOfPivot; // 记录哪列存在主元；第 i+1 个元素为0是此列不存在主元，不等于0是主元在此列的第几行；未计算则 PositionOfPivot.data 为 nullptr
```
### 构造函数 (public):
```c++
Matrix(int r, int c); // 创建一个 r 行 c 列的零矩阵
Matrix(int size); // 创建一个 size 行 size 列的单位矩阵
Matrix(); // 创建一个 1 行 1 列的零矩阵
Matrix(char c); // 创建一个 0 行 0 列的矩阵，不用管c是啥只要有就行，约等于声明一个变量，但是啥也没定义 (ps: 为什么不是上面函数那个干这件事，别问，问就是屎山)
Matrix(const Matrix& right); // 拷贝构造函数
```
### 析构函数
```c++
~Matrix();
```
### 成员函数 & 友元函数 (public)
#### 输入输出:
```c++
void impart(); // 从命令行输入，每个元素以空格隔开，什么时候回车并不重要，程序并不知道你要输入多大的矩阵，所以建议你先输入行数和列数，再用第一个构造函数定义变量，然后再用这个输入
void print(); // 在命令行输出, 
void print(int digit); // 在命令行里输出，但是每个元素只输出 digit位
void printALLinfo(); // 输出矩阵的所有信息
```
#### 对变量的操作：
```c++
int getNumOfColumn(); // 获取行数
int getNumOfrow(); // 获取列数
double getData(int r, int c); // 获取第 r+1 行第 c+1 列的元素的值
Vector RowOfMatrix(int Num_r) const; // 获取第 r+1 行的一整行
Vector ColumnOfMatrix(int Num_c) const; // 获取第 c+1 列的一整列
void fill(double a); // 将整个矩阵的每个元素赋值为 a
void ErrorToZero(); // 消除接近零的浮点数误差：如果矩阵中哪个元素与零的差小于epsilon(=1e-15)，就认为它是零，并赋值为零
friend Matrix CombineMatrix(const Matrix& left, const Matrix& right, char direction); // 将两个矩阵拼成一个矩阵，最后那个direction有两个取值是有用的：'H'表示H两个矩阵水平拼接，left在左right在右；'V'表示两个矩阵垂直拼接，left在上right在下
friend Matrix CombineMatrix(const Matrix& left, const Vector& right, char direction, char position); // 将一个矩阵和一个向量拼接成一个矩阵。direction取'H'是矩阵和向量水平拼接；取'V'是竖直拼接。position取'F'是向量在前/上；取'B'是向量在后/下
```
#### 矩阵运算：
```c++
void RowOperation_MultiplyScalar(int Num_r, double Num); // 行操作之数乘一行，将第 Num_r+1 行的每一个元素乘以 Num
void RowOperation_ExchangeRow(int Num_r_1, int Num_r_2); // 行操作之交换两行
void RowOperation_AddOneRowToAnother(int Num_r_1, int Num_r_2, double Num); // 行操作之，将第 Num_r_2+1 行的每个元素乘以 Num 加到 第Num_r_1+1 行的每个元素上
void REF(); // 将矩阵通过行化简操作转换至行梯形矩阵(row echelon form)
void RREF(); // 先调用.REF()，然后继续化简之化简行梯形矩阵(reduced row echelon form)
int Rank(); // 计算矩阵的秩，如果行化简过，直接输出成员变量rank的值，如果没有，现场算一下
double Det(); // 计算此矩阵的行列式，只有方阵才能计算行列式，如果矩阵大于3则用行化简来计算
friend Matrix Transpose(const Matrix& A); // 计算矩阵的转置，输出一个矩阵（不改变此矩阵）
friend Matrix Inverse(const Matrix& A); // 计算矩阵的逆（暂时使用行化简，LU分解还没做呢）
```
### 运算符重载：
```c++
Matrix& operator=(const Matrix& right); // 重载 赋值运算符，深拷贝
friend bool operator== (const Matrix& left, const Matrix& right); // 重载 等于号
friend Matrix operator+ (const Matrix& left, const Matrix& right); // 重载 加号
friend Matrix operator- (const Matrix& left, const Matrix& right); // 重载 减号
friend Matrix operator* (const double num, const Matrix& right); // 重载 乘号， 一个double的浮点数乘一个矩阵
friend Matrix operator* (const int num, const Matrix& right); // 重载 乘号，一个int整数乘一个矩阵
friend Matrix operator* (const Matrix& left, const Matrix& right); // 重载 乘号，一个矩阵乘一个矩阵
friend Matrix operator* (const Matrix& left, const Vector& right); // 重载 乘号， 一个矩阵乘一个向量，结果理论上是向量，但是一列的矩阵不也一样嘛
```
### 其他 (此处只是列出，功能介绍在后面)
```c++
friend class solutionOfLinearEquation;
friend solutionOfLinearEquation SolveLinearEquation(const Matrix& A, const Vector& b);
friend Matrix leastSquareMethod(const Matrix& X, const Vector& Y);
```
## **3. ```fraction```类**
## **4. ```Matrix_f```类**
## **5. 其他**
___
# 版本
## **v1.0**
- 第一版, 包括： ```matrix.cpp```、```matrix.hpp```、```makefile```、```leastSquareRegression.cpp```、```RREF.cpp```、```balanceTheChemicalRecation.cpp```、```gram_schmidt.cpp```
## **v1.1**
- 修复了一些BUG；添加了```README.md```文档
## **v1.2** 
- 修复一些BUG；添加了分数类型、分数类型的矩阵
## **v1.3**
- 修复了一些分数类型的BUG并完善其功能；重点改进```balanceTheChemicalRecation.cpp```：添加从命令行以 LaTeX 格式输入输出并自动识别元素填充矩阵以方便使用；添加了最小二乘后计算确定系数来评估模型好坏；完善了README.md
___

