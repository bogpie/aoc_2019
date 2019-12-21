#include <fstream>
#include <iostream>
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


	vector <int> vDigits;
	for (int iCar = 0; iCar < length; ++iCar)
	{
		int digit = line[iCar] - '0';
		vDigits.push_back(digit);
	}
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		auto vDigitsNew = vDigits;
		for (int iPattern = 0; iPattern < length; ++iPattern)
		{
			int sum = 0;
			for (int iDigit = 0; iDigit < length; ++iDigit)
			{
				sum += vDigits[iDigit] * vPatterns[iPattern][iDigit];
			}
			vDigitsNew[iPattern] = abs(sum) % 10;
		}
		vDigits = vDigitsNew;
	}

	fout << "part 1: ";
	for (int iDigit = 0; iDigit < 8; ++iDigit)
	{
		fout << vDigits[iDigit];
	}
	fout << "\n";

}


void fPart2(string line)
{
	vector <int> vDigits;
	int length = line.size();

	for (int iCar = 0; iCar < length; ++iCar)
	{
		int digit = line[iCar] - '0';
		vDigits.push_back(digit);
	}
	// string "turns into" a vector of digits 


	int offset = 0,pwr=1;
	for (int iDigit = 6; iDigit >= 0; --iDigit)
	{
		offset += (vDigits[iDigit] * pwr);
		pwr *= 10;
	}
	// computed offset



	auto vDigitsOld = vDigits;
	const int nRepeats = 9999;
	for (int iRepeat = 0; iRepeat < nRepeats; ++iRepeat)
	{
		vDigits.insert(vDigits.end(), vDigitsOld.begin(), vDigitsOld.end());
	}
	// there are now 10000 times of the given input

	length = vDigits.size();
	if (offset > length)
	{
		fout << "offset too big!";
		cout << "offset too big!";
		exit(1);
	}

	vDigits.erase(vDigits.begin(), vDigits.begin() + offset);
	//erase everything until the offset

	length = vDigits.size();
	for (int iStep = 1; iStep <= 100; ++iStep)
	{
		for (int iDigit = length - 2; iDigit >= 0; --iDigit)
		{
			vDigits[iDigit] = (vDigits[iDigit] + vDigits[iDigit + 1]) % 10;
		}
	}
	// compute partial sums 100 times

	fout << "part 2: ";
	for (int iDigit = 0; iDigit < 8; ++iDigit)
	{
		fout << vDigits[iDigit];
	}
	fout << "\n";
	//print first 8 digits
	

}

int main()
{
	string line;
	fin >> line;

	fPart1(line);
	cout << "part 1 done, wait a few seconds for part 2..\n";
	fPart2(line);

	return 0;
}