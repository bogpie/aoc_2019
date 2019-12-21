#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("d16_in.txt");
ofstream fout("d16_out.txt");

void generatePatterns(int nPattern, vector < vector <int > >  & vPattern)
{
	vector<int> vValues{ 0,1,0,-1 };
	for (int iPattern = 0; iPattern < nPattern; ++iPattern)
	{
		int iValue = 0;

		vPattern[iPattern].push_back(vValues[0]);
		for (int iDigit = 1; iDigit < nPattern; ++iDigit)
		{
			if ((iDigit + 1) % (iPattern + 1) == 0)
			{
				iValue = (iValue + 1) % 4;
			}
			vPattern[iPattern].push_back(vValues[iValue]);
		}
	}
}

int main()
{
	string line;
	fin >> line; 

	vector < vector <int > > vPattern(line.size()+1);
	generatePatterns(line.size(),vPattern);

	vector <int> vDigit;
	for (int iCar = 0; iCar < line.size(); ++iCar)
	{
		int digit = line[iCar] -'0';
		vDigit.push_back(digit);
	}
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		for (int iPattern = 0; iPattern < line.size(); ++iPattern)
		{
			for (int iDigit = 0; iDigit < line.size(); ++iDigit)
			{
				vDigit[iPattern] += vDigit[iDigit] * vPattern[iPattern][iDigit];
			}
		}
	}

	return 0;
}