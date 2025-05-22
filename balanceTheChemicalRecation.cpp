#include "matrix.hpp"

class stringAndString
{
    private:
        int size;
        std::string* data;
    public:
        // constructor
        stringAndString();
        stringAndString(int s);
        // destroyer
        ~stringAndString();
        // member function
        std::string getString(int a);
        void printAll();
        void print(int a);
        void add(std::string a);
        int getSize();
        int isInString(std::string h);
        void insert(int num, int i, std::string ss);
        void deleteI(int num, int i, int j);
        stringAndString& operator=(const stringAndString& right);
} ;

stringAndString::stringAndString() : size(0)
{
    data = nullptr; //new std::string[size];
}
stringAndString::stringAndString(int s) : size(s)
{
    data = new std::string[size]; //new std::string[size];
}
stringAndString::~stringAndString()
{
    if(data)
        delete[] data;
}
std::string stringAndString::getString(int a)
{
    if(a < 0 || a >= size)
        PrintSadCat("stringAndString::getString: int a is bigger than size, or smaller than 0");
    return data[a];
}
void stringAndString::printAll()
{
    for(int i = 0; i < size; i++)
        std::cout << data[i] <<' ';
    std::cout << std::endl;
}
void stringAndString::print(int a)
{
    std::cout << data[a];
}
void stringAndString::add(std::string a)
{
    if(data == nullptr)
    {
        data = new std::string[1];
        size = 1;
        data[0] = a;
        return;
    }
    stringAndString temp(size + 1);
    for(int i = 0; i < size; i++)
        temp.data[i] = data[i];
    temp.data[size] = a;
    delete[] data;
    size+=1;
    data = new std::string[size];
    for(int i = 0; i < size; i++)
        data[i] = temp.data[i];
}
int stringAndString::getSize()
{
    return size;
}
int stringAndString::isInString(std::string h) // 为了同时用到 int 和 bool，0就是false，任何大于零都是true，正好，所以做下标的话要i-1
{
    if(data == nullptr)
        return 0;
    for(int i = 0; i < size; i++)
        if(data[i] == h)
            return i+1;
    return 0;
}
void stringAndString::insert(int num, int i, std::string ss)
{
    data[num].insert(i, ss);
}
void stringAndString::deleteI(int num, int i, int j)
{
    // std::cout<<"\nfor string: "<<data[num]<<", from digit "<<i<<" to digit "<<j<<", we delete ";
    // for(int k = i; k <= j; k++)
    //     std::cout<<data[num][k];

    data[num].erase(i, j - i + 1);

    // std::cout<<"\nnow string is: "<<data[num]<<"\n";
}
stringAndString& stringAndString::operator=(const stringAndString& right)
{
    if(this != &right)
    {
        if(data)
            delete[] data;
        size = right.size;
        if(size > 0)
        {
            data = new std::string[size];
            for(int i = 0; i < size; i++)
                data[i] = right.data[i];
        }
        else
            data = nullptr;
    }
    return *this;
}

int main()
{
    // 输入格式，latex化学公式，可以不加 \ce{ }，**要每个物质前后用空格隔开**，不要配平，也不要加沉淀和其他的符号，中间用=、==、->、-->之一隔开。中间千万不要有换行符
    // 暂不支持离子方程式
    int num_elements = 0, num_r = 0, num_t = 0, temp_int, isAParantheses = 0; // isAParantheses同时承担bool和int的职责所以作为角标时要减一
    bool isASubstance = false, isAElement = false;
    stringAndString r, elements;

    std::string ss,temp, temp_e, temp_num; // 临时存储读取的字符串
    // ss = R"( K4Fe(CN)6 + KMnO4 + H2SO4 = KHSO4 + Fe2((Au3)2(SO4)11)3 + MnSO4 + HNO3 + CO2 + H2O )"; // test
    std::getline(std::cin,ss,'\n');
    ss += ' ';

    // 挨个读取字符串并识别物质
    for(int i = 0; i < ss.size(); i++)
    {
        if(isASubstance == false && ((ss[i] >= 'A' && ss[i] <= 'Z') || ss[i] == '(')) // 识别开头输入 大写26字母
        {
            isASubstance = true;
            temp += ss[i];
        }
        else if(isASubstance == true)
        {
            if(ss[i] == ' ' || ss[i] == '}' || i == ss.size() - 1)
            {
                isASubstance = false;
                r.add(temp);
                temp.clear();
                num_t ++;
            }
            else if(ss[i] == '(' || ss[i] == ')' || (ss[i] >= '0' && ss[i] <= '9') || (ss[i] >= 'A' && ss[i] <= 'Z') || (ss[i] >= 'a' && ss[i] <= 'z'))
                temp += ss[i];
            else
            {
                PrintSadCat("wrong input form, ask Emma");
            }
        }
        else if(ss[i] == '=' || ss[i] == '-')
            num_r = num_t;
    }

    stringAndString forOutPut;
    forOutPut = r;

    // 将所有括号拆开
    // 挨个处理物质 //扫描记录的数据，从里到外挨个将括号拆开
    for(int num_e = 0; num_e < r.getSize(); num_e++)
    {
        // 对于每个物质，先从头到尾扫描一遍，记录下所有括号的位置和下标
        Matrix_f Parantheses; //其实用整数最划算但是我这里没整数的矩阵而分数的后来写的其实更严谨就用fraction凑活一下吧，初始是空矩阵，一共三列，第一列起始位置第二列终止位置第三列下标
        for(int i = 0; i < r.getString(num_e).size(); i++)
        {
            temp.clear();
            temp = r.getString(num_e);
            if(isAParantheses)
            {
                if(temp[i] == ')')
                {
                    isAParantheses --;
                    Parantheses.writeElements(isAParantheses, 1, i);
                    if(i+1 < temp.size())
                    {
                        if(temp[i+1] >= '0' && temp[i+1] <= '9')
                        {
                            temp_num.clear();
                            for(int tmd = i+1; tmd <= temp.size() && temp[tmd]>='0' && temp[tmd]<='9'; tmd++)
                            {
                                temp_num += temp[tmd];
                            }
                            Parantheses.writeElements(isAParantheses, 2, std::stoi(temp_num));
                        }
                        else 
                            Parantheses.writeElements(isAParantheses, 2, 1);
                    }
                    else
                        Parantheses.writeElements(isAParantheses, 2, 1);
                    // 展开括号，矩阵parantheses也删去一行
                    int place = fToi(Parantheses.getElements(isAParantheses, 0));
                    std::string copying;
                    for(int idk = place + 1; idk < fToi(Parantheses.getElements(isAParantheses, 1)); idk++)
                        copying += temp[idk];
                    r.deleteI( num_e, place, fToi(Parantheses.getElements(isAParantheses, 1)) + std::to_string(fToi(Parantheses.getElements(isAParantheses, 2))).size() ); // 删除原来两个括号
                    for(int idk = 0; idk < fToi(Parantheses.getElements(isAParantheses, 2)); idk++)
                    {
                        r.insert(num_e, place, copying);
                        place += copying.size();
                    }
                    Parantheses.deleteOneLastRow();
                }
            }
            if(temp[i] == '(')
            {
                isAParantheses ++;
                Matrix_f sb(1, 3);// paranatheses matrix新增加一列
                Parantheses = CombineMatrix(Parantheses, sb, 'V');
                Parantheses.writeElements(isAParantheses-1, 0, i);
            }
        }
        if(isAParantheses) // 括号是成对出现的，++ 和 --的数量必须相等
            PrintSadCat("wrong input format of substance, since there is a '(' but no ')' ");
    }

    // // test
    // std::cout<<'\n';
    // r.printAll();
    // std::cout<<'\n';

    // 挨个处理每个物质识别元素，生成系数矩阵
    Matrix_f www, temp_horizontal(1, num_t);// www is the coefficient matrix, and paranthesis is the matrix for mark the position of paranthesis, rows are one layer of paranathesis
    temp_horizontal.fill(0);
    for(int num_e = 0; num_e < r.getSize(); num_e++) 
    {
        temp.clear();
        temp_num.clear();
        temp = r.getString(num_e);
        for(int i = 0; i <= temp.size(); i++)
        {
            // 识别元素
            if(i < temp.size() && isAElement == false && (temp[i] >= 'A' && temp[i] <= 'Z')) // 判断元素
            {
                isAElement = true;
                temp_e += temp[i];
            }
            else if(isAElement == true)
            {
                // test std::cout << "the "<<num_e + 1<<"个物质 第"<<i<<"位\n";
                if(i < temp.size() && temp[i] >= 'a' && temp[i] <= 'z')
                    temp_e += temp[i];
                else if(i < temp.size() && temp[i] >= '0' && temp[i] <= '9')
                    temp_num += temp[i];
                if( i == temp.size() || (temp[i]>='A' && temp[i]<='Z') || (temp[i] == '(' || temp[i] == ')') ) // 识别完一个完整的元素和其化学计量数，检查是否已知，并计数
                {
                    isAElement = false;
                    // 先处理化学计量数
                    if(temp_num.empty())
                        temp_int = 1;
                    else
                        temp_int = std::stoi(temp_num);
                    temp_num.clear();
                    // 判断是否是已知元素，是，处理；不是，添加一行再处理
                    if(int is = elements.isInString(temp_e))
                        www.writeElements(is - 1, num_e, www.getElements(is - 1, num_e) + temp_int);
                    else
                    { // 不是已知元素，添加一行
                        num_elements++;
                        elements.add(temp_e); // test std::cout << "       the "<<num_e + 1<<"个物质 第"<<i<<"位 add new elements: "<<temp_e<<'\n';
                        www = CombineMatrix(www, temp_horizontal, 'V');
                        www.writeElements(elements.getSize() -1, num_e, temp_int);
                    }
                    temp_e.clear();
                    if(i < temp.size() && temp[i] != '(' && temp[i] != ')' )
                    {
                        isAElement = true;
                        temp_e += temp[i];
                    }
                }
                // else
                //     PrintSadCat("mayday! mayday! mayday!");
            }
        }
    }

    // 构造好系数矩阵和零向量
    for(int j = num_r; j < num_t ; j++)
    {
        www.ColumnOperation_MultiplyScalar(j, -1);
    }
    Matrix_f z(num_elements, 1);
    z.fill(0);

    // // test
    // for(int j = 0; j < num_t; j++)
    // {
    //     std::cout << r.getString(j) << ":\n";
    //     for(int i = 0; i < num_elements; i++)
    //     {
    //         std::cout << "    " << elements.getString(i) << ": ";
    //         wjqLovesHqy.getElements(i, j).print();
    //     }
    //     std::cout << "\n";
    // }

    // //test
    // www.printALLinfo();

    www = SolveLinearEquationAndPrint(www, z);
    www.clearTheDenominator(1, -1);

    // // test
    // www.printALLinfo();

    std:: cout << "\n\n\n";
    if(www.getCols() < 2)
        std::cout << "此化学方程式无解，请检查您的输入";
    else{
        if(www.getCols() > 2)
            std::cout << "此化学方程式式自由变量多于1, 此处只展示一种配平方法";
        for(int i = 0; i < num_t; i++)
        {
            if(i == num_r)
                std::cout << " -> ";
            if(www.getElements(i, 1) > 1)
                www.getElements(i, 1).print();
            forOutPut.print(i);
            if(i != num_t - 1 && i != num_r - 1)
                std::cout << " + ";
        }
    }
    PrintHappyCat();
    std::cout << "\n";

    return 0;
}