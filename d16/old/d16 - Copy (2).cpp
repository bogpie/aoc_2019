#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("d16_in.txt");
ofstream fout("d16_out.txt");

void generatePatterns(int nPatterns, vector < vector <int > >& vPatterns)
{
	vector<int> vValues{ 0,1,0,-1 };

	int iPattern = 0;
	while (iPattern < nPatterns)
	{
		int iValue = 0;
		int iDigit = 0;

		while (iDigit < nPatterns)
		{
			if ((iDigit + 1) % (iPattern + 1) == 0)
			{
				iValue = (iValue + 1) % 4;
			}

			vPatterns[iPattern].push_back(vValues[iValue]);

			++iDigit;
		}
		++iPattern;
	}

}
	


int main()
{
	string line;
	fin >> line; 
	int lineSize = line.size();
	vector < vector <int > > vPatterns(lineSize+1);
	generatePatterns(lineSize,vPatterns);


	vector <int> vDigit;
	for (int iCar = 0; iCar < lineSize; ++iCar)
	{
		int digit = line[iCar] -'0';
		vDigit.push_back(digit);
	}
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		auto vDigitNew = vDigit;
		for (int iPattern = 0; iPattern < lineSize; ++iPattern)
		{
			int sum = 0;
			for (int iDigit = 0; iDigit < lineSize; ++iDigit)
			{
				sum += vDigit[iDigit] * vPatterns[iPattern][iDigit];
			}
			vDigitNew[iPattern] = abs(sum) % 10 ;
		}
		vDigit = vDigitNew;
	}

	fout << "part 1: ";
	for (int iDigit = 0; iDigit < 8; ++iDigit)
	{
		fout << vDigit[iDigit];
	}
	fout << "\n";

	return 0;
}