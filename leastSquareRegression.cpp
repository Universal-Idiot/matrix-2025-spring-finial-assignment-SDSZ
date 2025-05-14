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
	std::fstream inputFile("/Users/qili/Desktop/Learning coding/learning C++/data.txt", std::ios::in);
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
	std::cout<<"\n the best fit linear funtion is: y = "<<ans.getData(0,0)<<" * x + "<<ans.getData(1,0)<<'\n';
 	inputFile.close();
    return 0;
}