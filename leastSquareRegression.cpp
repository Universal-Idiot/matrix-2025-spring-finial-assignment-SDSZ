#include "matrix.hpp"

bool isValidNumber(const std::string& str)
{
	try
	{
		std::stod(str);
		return true;
	}
	catch(...)
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	// if you wang to get a dynamic path
	// 1. get the absolute path of program
	// 2. get catalog of where the program is
	// 3. construct the path of file

	// open file
	std::fstream inputFile("/Users/qili/Desktop/Learning coding/codeOfLinearAlgebraAssignment/data.txt", std::ios::in);
;	if(!inputFile)
	{
		std::cerr << "\nError: unable to open file\n";
		return 1;
	}
	// input and seperate string, storing in Vector and matrix
	std::string str;
	Vector x, y;
	while(std::getline(inputFile, str, ','))
	{
		if(isValidNumber(str))
		{
			x.add(std::stod(str));
			if(getline(inputFile, str, '\n'))
			{
				y.add(std::stod(str));
			}
			else	
				std::cout<<"Error: idk...";
		}
	}
	Matrix ans=leastSquareMethod(x, y);
	if(ans.getData(1,0) >= 0)
		std::cout<<"\nthe best fit linear funtion is:\n y = "<<ans.getData(0,0)<<" * x + "<<ans.getData(1,0)<<'\n';
	else
		std::cout<<"\nthe best fit linear funtion is:\n y = "<<ans.getData(0,0)<<" * x - "<< -1 * ans.getData(1,0)<<'\n';
	std::cout<<"with a Coefficient of Determination(R^2): "<<ans.getData(7, 0);
	std::cout<<"\nwhich means we can explain "<<std::fixed << std::setprecision(2) << 100 * ans.getData(7, 0)<<R"(% of data by this regression model)";
	if(ans.getData(7, 0) > 0.9)
	{
		std::cout<<"\nIt is an excellent, wonderful, unexceptionable, admirable, Superlative, Transcendent, regression model, congratulation!";
		PrintHappyCat();
	}
	else if(ans.getData(7, 0) > 0.7)
	{
		std::cout<<"\nIt is a good regression model, have a good time!";
		PrintHappyCat();
	}
	else if(ans.getData(7, 0) > 0.5)
	{
		std::cout<<"\nThe regression model is just so so, but still useful!";
		PrintCat();
	}
	else if(ans.getData(7, 0) > 0.5)
		std::cout<<"\nIt is a bad regression model, and you'd better to change another model!\n"<<" Λ___Λ\n| T  T|\n|  _  |\n|     |\n";
	else
		std::cout<<"\nYour regression model is a shit of garbage, and you should fuck yourself!\n"<<" Λ___Λ\n| T  T|\n|  _  |\n|     |\n";
	inputFile.close();
    return 0;
}