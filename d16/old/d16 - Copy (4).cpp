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


void fPart1(string line)
{
	int length = line.size();
	vector < vector <int > > vPatterns(length + 1);
	generatePatterns(length, vPatterns);


	vector <int> vDigit;
	for (int iCar = 0; iCar < length; ++iCar)
	{
		int digit = line[iCar] - '0';
		vDigit.push_back(digit);
	}
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		auto vDigitNew = vDigit;
		for (int iPattern = 0; iPattern < length; ++iPattern)
		{
			int sum = 0;
			for (int iDigit = 0; iDigit < length; ++iDigit)
			{
				sum += vDigit[iDigit] * vPatterns[iPattern][iDigit];
			}
			vDigitNew[iPattern] = abs(sum) % 10;
		}
		vDigit = vDigitNew;
	}

	fout << "part 1: ";
	for (int iDigit = 0; iDigit < 8; ++iDigit)
	{
		fout << vDigit[iDigit];
	}
	fout << "\n";

}


void fPart2(string line)
{
	vector <int> vDigit;
	int length = line.size();

	for (int iCar = 0; iCar < length; ++iCar)
	{
		int digit = line[iCar] - '0';
		vDigit.push_back(digit);
	}

	int offset = 0,pwr=1;

	for (int iDigit = 6; iDigit >= 0; --iDigit)
	{
		offset += (vDigit[iDigit] * pwr);
		pwr *= 10;
	}

	auto vDigitOld = vDigit;
	const int nRepeats = 10000;
	for (int iRepeat = 0; iRepeat < nRepeats; ++iRepeat)
	{
		vDigit.insert(vDigit.end(), vDigitOld.begin(), vDigitOld.end());
	}
	vDigit.erase(vDigit.begin(), vDigit.begin() + offset);

	length = vDigit.size();
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		// vDigit[length-1] constant 
		for (int iDigit = length - 2; iDigit > 0; --iDigit)
		{
			vDigit[iDigit] = (vDigit[iDigit] + vDigit[iDigit + 1]) % 10;
		}
	}

	fout << "part 2: ";
	for (int iDigit = 0; iDigit < 8; ++iDigit)
	{
		fout << vDigit[iDigit];
	}
	fout << "\n";
}

int main()
{
	string line;
	fin >> line;

	//fPart1(line);
	fPart2(line);

	return 0;
}