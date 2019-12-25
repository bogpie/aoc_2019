#include <fstream>
#include <set>
#include <vector>


using namespace std;

ifstream fin("d24_in.txt");
ofstream fout("d24_out.txt");

int fConvert(char car)
{
	if (car == '.') return 0;
	if (car == '#') return 1;
	
	//else
	
	fout << "Error";
	exit(1);
}

void fTransform(vector < vector < int > > & newMatrix)
{
	auto oldMatrix = newMatrix;
	for (int iTall = 1; iTall <= oldMatrix.size() - 2; ++iTall)
	{
		for (int iWide = 1; iWide <= oldMatrix[iTall].size() - 2; ++iWide)
		{
			int tile = oldMatrix[iTall][iWide];

			if (tile == 0)
			{
				int nBugs = oldMatrix[iTall - 1][iWide] + oldMatrix[iTall + 1][iWide] + oldMatrix[iTall][iWide - 1] + oldMatrix[iTall][iWide + 1];
				if (nBugs == 1 || nBugs==2)
				{
					newMatrix[iTall][iWide] = 1;
				}
			}
			else if (tile == 1)
			{
				int nBugs = oldMatrix[iTall - 1][iWide] + oldMatrix[iTall + 1][iWide] + oldMatrix[iTall][iWide - 1] + oldMatrix[iTall][iWide + 1];
				if (nBugs != 1)
				{
					newMatrix[iTall][iWide] = 0;
				}
			}
			else
			{
				fout << "Error";
				exit(1);
			}
		}
	}
}

int computeRating(vector < vector < int > > matrix)
{
	int rating = 0;

	for (int iTall = 1; iTall <= matrix.size() - 2; ++iTall)
	{
		for (int iWide = 1; iWide <= matrix[iTall].size() - 2; ++iWide)
		{
			if (matrix[iTall][iWide])
			{
				int iTile = ((iTall-1) * 5 + iWide);
				rating += (1 << (iTile-1));
			}
		}
	}
	return rating;
}

void fPrint(vector < vector < int > > matrix)
{
	for (int iTall = 0; iTall < matrix.size(); ++iTall)
	{
		for (int iWide = 0; iWide < matrix[iTall].size(); ++iWide)
		{
			fout << matrix[iTall][iWide] << " ";
		}
		fout << "\n";
	}
	fout << "\n";
	fout << "\n";

}

void fPart1(vector <string> layout)
{

	vector < vector < int > > matrix(7);
	matrix[0].resize(7, 0);
	matrix[6].resize(7, 0);
	for (int iTall = 0; iTall < layout.size(); ++iTall)
	{
		matrix[iTall + 1].push_back(0);
		for (int iWide = 0; iWide < layout[iTall].size(); ++iWide)
		{
			matrix[iTall + 1].push_back(fConvert(layout[iTall][iWide]));
		}
		matrix[iTall + 1].push_back(0);
	}

	// decided to use an int matrix for part 1
	
	set < vector < vector < int > > > states;
	states.insert(matrix);

	//fPrint(matrix);
	while (1)
	{
		fTransform(matrix);
		//fPrint(matrix);
		if (states.find(matrix) != states.end())
		{
			break;
		}
		states.insert(matrix);
	}

	int rating = computeRating(matrix);

	fout << "part 1: " << rating << "\n";
}

void fPart2(vector <string> layout)
{
	string str;
	vector <string> emptyLayout;
	emptyLayout.resize(5);
	for (int iTall= 0; iTall < 5; ++iTall)
	{
		emptyLayout.push_back(".....");
	}
	emptyLayout[2][2] = '?';
	vector < vector < string > > vFloor;
	for (int iFloor = 0; iFloor < 200; ++iFloor)
	{
		vFloor.push_back(emptyLayout);
	}
	vFloor.push_back(layout);
	for (int iFloor = 0; iFloor < 200; ++iFloor)
	{
		vFloor.push_back(emptyLayout);
	}

	int low = 199;
	int high = 201;
	for (int iMinute=1;iMinute<=200;++iMinute)
		for (int iFloor = low; iFloor <= high; ++iFloor)
		{
			for (int iTall = 0; iTall < 5; ++iTall)
			{
				for (int iWide = 0; iWide < 5; ++iWide)
				{
					exit(1);
					//unfinished
				}
			}
		}
}

int main()
{

	string str;
	vector <string> layout;


	while (fin >> str)
	{
		layout.push_back(str);
	}
	fPart1(layout);
	//fPart2(layout);
	return 0;
}