#include <fstream>
#define NWIDE 25
#define NTALL 6

using namespace std;

ifstream fin("d08_in.txt");
ofstream fout("d08_out.txt");

void fInitializePhoto(char vPhoto[NTALL][NWIDE], int nWide, int nTall)
{
	for (int iTall = 0; iTall < nTall; ++iTall)
	{
		for (int iWide = 0; iWide < nWide; ++iWide)
		{
			vPhoto[iTall][iWide] = '2';
		}
	}
}
void fPrintPhoto(char vPhoto[NTALL][NWIDE], int nWide, int nTall)
{
	for (int iTall = 0; iTall < nTall; ++iTall)
	{
		for (int iWide = 0; iWide < nWide; ++iWide)
		{
			if (vPhoto[iTall][iWide] == '0') fout << "  ";
			else fout << vPhoto[iTall][iWide] << ' ';
		}
		fout << '\n';
	}
}

int main()
{
	const int nWide = 25;
	const int nTall = 6;

	char vPhoto[NTALL][NWIDE];
	int sol1=0, iWide = 0,iTall = 0,nMinZeroes=nWide*nTall+1, vCount[3] = { 0 };
	char chr;
	
	fInitializePhoto(vPhoto,nWide,nTall);
	
	while (fin >> chr)
	{
		++vCount[chr - '0'];
		
		if (vPhoto[iTall][iWide] == '2')
		{
			vPhoto[iTall][iWide] = chr;
		}

		++iWide;
		if (iWide == nWide)
		{
			++iTall;
			iWide = 0;
			if (iTall == nTall)
			{
				if (vCount[0] < nMinZeroes)
				{
					nMinZeroes = vCount[0];
					sol1 = vCount[1] * vCount[2];
				}
				iTall = 0;
				vCount[0] = vCount[1] = vCount[2] = 0;
			}
		}
	}

	fout << "part 1 : " << sol1 << "\n";
	fout << "part 2 :\n";
	fPrintPhoto(vPhoto, nWide, nTall);

	return 0;
}