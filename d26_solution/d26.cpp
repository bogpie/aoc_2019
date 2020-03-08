#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("d26_out.txt");

void fInlocuireCar(string & str)
{
	while (1)
	{
		int poz = str.find("N");
		if (poz == -1) break;
		str[poz] = ' ';
	}
}

void fGasesteDiv(int numar, int divMinim, vector <int>& vDiv)
{
	for (int div = divMinim; div <= numar; ++div)
	{
		if (numar % div == 0)
		{
			vDiv.push_back(div);
void fPrint(string str, vector <int> vDiv)
{
	vector <int>::iterator it;
	for (it = vDiv.begin(); it != vDiv.end(); ++it)
	{
		int nCol = *it;
		int iStr = 0;

		fout << nCol << " caractere pe linie : \n";
		while (iStr < str.size())
		{
			for (int iCol = 0; iCol < nCol; ++iCol)
			{
				fout << str[iStr++];
			}
			fout << "\n";
		}
		fout << "\n\n\n";
	}

}

void fPrintSpecific(string str, int nCol)
{
	
	int iStr = 0;

	fout << nCol << " caractere pe linie : \n";
	while (iStr < str.size())
	{
		for (int iCol = 0; iCol < nCol; ++iCol)
		{
			fout << str[iStr++];
		}
		fout << "\n";
	}
	fout << "\n\n\n";

}

int main()
{
	string str;
	fin >> str;
	fInlocuireCar(str);
	
	vector < int > vDiv;
	int numar = 72000;
	int divMinim = 100;
	fGasesteDiv(numar,divMinim,vDiv);
	
	int nCol = 500;
	fPrintSpecific(str,nCol); // aici putem printa un numar specificat de coloane, eu am ales 500 fiindca, in urma afisarii cu functia fPrint apelata mai jos, am observat ca la acest numar imaginea pare decodificata
	fPrint(str, vDiv);
	
	return 0;
}