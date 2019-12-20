#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ifstream fin("d14_in.txt");
ofstream fout("d14_out.txt");

int main()
{
	string line;
	map < string, pair < int, vector < pair < int, string > >> > mapReaction;

	while (!fin.eof())
	{
		int nElem;
		string strElem;
		
		vector < pair < int, string > > vPairElem;
		while (1)
		{
			fin >> nElem;
			if (!nElem)
			{
				char car;
				fin >> car;
				fin >> car;
				fin >> nElem >> strElem;
				pair < int, vector < pair < int, string > >> pairReaction(nElem, vPairElem);
				mapReaction[strElem] = pairReaction;
				break;
			}
			fin >> strElem;
			pair < int, string > pairElem(nElem,strElem);
			vPairElem.push_back(pairElem);
		
		} 
	}
	



	return 0;
}