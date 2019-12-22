#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("d17_in.txt");
ofstream fout("d17_out.txt");
ofstream tabFile("tabFile.txt");
ofstream pathFile("pathFile.txt");

vector < pair < int, int >  > vDir{ make_pair(-1,0),make_pair(+1,0),make_pair(0,-1),make_pair(0,+1) };
vector < char > vCar{ 'L','R' };

void fParse(vector <long long>& vProg)
{
	long long x;
	char comma;
	while (fin >> x)
	{
		fin >> comma;
		vProg.push_back(x);
		if (comma == '\0')
		{
			break;
		}
	}
	vProg.resize(vProg.size() + 4, 0); //vProg.resize(nr,val);
	return;
}

void fParseInstruction(long long& opcode, long long instruction, long long vParamMode[])
{
	opcode = instruction % 100;
	long long divide = 100;
	for (long long iParam = 1; iParam <= 3; ++iParam)
	{
		vParamMode[iParam] = instruction / divide % 10;
		divide *= 10;
	}
}



void fFindSingleParameter(vector <long long> vProg, long long iProg, long long relBase, long long vParam[], long long iParam, long long vParamMode[])
{
	long long param = vProg[iProg + iParam];
	long long paramMode = vParamMode[iParam];
	if (paramMode != 1)
	{
		long long position = param + (paramMode == 2) * relBase;

		if (position < 0 || position >= vProg.size())
		{
			vProg.resize(position + 3, 0);
		}

		if (paramMode == 0)
		{
			param = vProg[param];
		}
		else if (paramMode == 2)
		{
			param = vProg[param + relBase];

		}
	}

	vParam[iParam] = param;

}

void fFindParameters(vector <long long> vProg, long long iProg, long long relBase, long long vParam[], long long vParamMode[], long long opcode)
{
	if (opcode != 99 && opcode != 3)
	{
		fFindSingleParameter(vProg, iProg, relBase, vParam, 1, vParamMode);
		if (opcode != 4 && opcode != 9)
		{
			fFindSingleParameter(vProg, iProg, relBase, vParam, 2, vParamMode);
		}
	}
}

void fRunProgram(queue <int> inputQue, vector <long long> vProg, vector <long long >& vOutputs)
{
	long long iProg = 0, relBase = 0;
	long long steps = 0;


	while (iProg >= 0)
	{
		if (iProg > vProg.size()) vProg.resize(iProg + 4, 0);
		long long instruction = vProg[iProg], vParamMode[4], opcode;
		fParseInstruction(opcode, instruction, vParamMode);

		long long vParam[4];
		fFindParameters(vProg, iProg, relBase, vParam, vParamMode, opcode);

		switch (opcode)
		{
		case 1:
		{
			long long position3 = vProg[iProg + 3];

			if (vParamMode[3] == 2)
			{
				position3 += relBase;
			}
			if (position3 >= vProg.size()) vProg.resize(position3 + 4, 0);

			vProg[position3] = vParam[1] + vParam[2];
			iProg += 4;
			break;
		}
		case 2:
		{

			long long position3 = vProg[iProg + 3];

			if (vParamMode[3] == 2)
			{
				position3 += relBase;
			}
			if (position3 >= vProg.size()) vProg.resize(position3 + 4, 0);

			vProg[position3] = vParam[1] * vParam[2];
			iProg += 4;
			break;
		}
		case 3:
		{
			long long position1 = vProg[iProg + 1];

			if (vParamMode[1] == 2)
			{
				position1 += relBase;
			}
			if (position1 >= vProg.size()) vProg.resize(position1 + 4, 0);

			if (!inputQue.empty())
			{
				vProg[position1] = inputQue.front();
			}
			else
			{
				fout << "something's wrong!\n";
				exit(1);
			}
			inputQue.pop();

			iProg += 2;
			break;
		}
		case 4:
		{
			long long output = vParam[1];
			//fout << "Output: " << output << '\n';
			vOutputs.push_back(output);
			iProg += 2;
			break;
		}
		case 5:
		{
			if (vParam[1])
			{
				iProg = vParam[2];
			}
			else
			{
				iProg += 3;
			}
			break;
		}
		case 6:
		{

			if (!vParam[1])
			{
				iProg = vParam[2];
			}
			else
			{
				iProg += 3;
			}
			break;
		}
		case 7:
		{


			long long position3 = vProg[iProg + 3];


			if (vParamMode[3] == 2)
			{
				position3 += relBase;
			}
			if (position3 >= vProg.size()) vProg.resize(position3 + 4, 0);

			vProg[position3] = (vParam[1] < vParam[2]);
			iProg += 4;
			break;
		}
		case 8:
		{

			long long position3 = vProg[iProg + 3];

			if (vParamMode[3] == 2)
			{
				position3 += relBase;
			}
			if (position3 >= vProg.size()) vProg.resize(position3 + 4, 0);

			vProg[position3] = (vParam[1] == vParam[2]);
			iProg += 4;
			break;
		}
		case 9:
		{
			relBase += vParam[1];
			iProg += 2;
			break;
		}
		case 99:
		{
			//fout << "Halted !\n";
			iProg = -1;
			//exit(1);
			break;
			return;
		}
		}
	}
}

bool isVacuum(char car)
{
	if (car == '^' || car == 'v' || car == '<' || car == '>')
	{
		return 1;
	}
	return 0;
}

int find_id_dir(char car)
{
	if (car == '^')
	{
		return 0;
	}
	if (car == 'v')
	{
		return 1;
	}
	if (car == '<')
	{
		return 2;
	}
	if (car == '<')
	{
		return 3;
	}
}

int find_id_dir_new(int idDir, int idTurn)
{
	if (idDir == 0) //north - > left / right
	{
		if (idTurn == 0) 
		{
			return 2; 
		}
		return 3;
	}
	if (idDir == 1) // south
	{
		if (idTurn == 0)
		{
			return 3;
		}
		return 2;
	}
	if (idDir == 2) // west
	{
		if (idTurn == 0)
		{
			return 1;
		}
		return 0;
	}
	if (idDir == 3) // east
	{
		if (idTurn == 0)
		{
			return 0;
		}
		return 1;
	}
}

void fPrintTab(vector < string > tab)
{
	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		for (int iWide = 0; iWide < tab[iTall].size(); ++iWide)
		{
			tabFile << tab[iTall][iWide];
		}
		tabFile << '\n';
	}

}

void fCreateTab(vector <long long> vOutputs, vector < string > & tab)
{
	int nOutputs = vOutputs.size();

	tab[0].push_back(0);

	int iTall = 1;
	tab[1].push_back(0);

	for (int iOutput = 0; iOutput < nOutputs; ++iOutput)
	{
		if (vOutputs[iOutput] == 10)
		{
			tab[iTall].push_back(0);
			tab.resize(tab.size() + 1);
			++iTall;
			tab[iTall].push_back(0);
		}
		else
		{
			tab[iTall].push_back((char)vOutputs[iOutput]);
		}
	}
	for (int iTall = tab.size() - 1; iTall >= 0; --iTall)
	{
		if (tab[iTall].size() < tab[1].size())
		{
			tab.pop_back();
		}
		else
		{
			break;
		}
	}
	tab.resize(tab.size() + 1);

	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		tab[iTall].resize(tab[1].size());
	}
}

void fFindSum(int& sum, vector < string > tab)
{
	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		for (int iWide = 0; iWide < tab[iTall].size(); ++iWide)
		{

			if (tab[iTall][iWide] == '#' && tab[iTall - 1][iWide] == '#' && tab[iTall + 1][iWide] == '#' && tab[iTall][iWide - 1] == '#' && tab[iTall][iWide + 1] == '#')
			{
				sum += ((iTall - 1) * (iWide - 1));
			}
		}
	}
}

void fFindVacuum(pair <int, int >& vacuum, vector < string > tab)
{
	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		for (int iWide = 0; iWide < tab[iTall].size(); ++iWide)
		{
			if (isVacuum(tab[iTall][iWide]))
			{
				vacuum = make_pair(iTall, iWide);
				break;
			}

		}
	}
}
void fFindPath(vector <string> tab, pair<int,int> vacuum)
{
	int idDir = idDir = find_id_dir(tab[vacuum.first][vacuum.second]), nSteps = 0, idTurnLast = 0;

	queue < pair <int, int > > que;
	que.push(vacuum);

	while (!que.empty())
	{
		int x = que.front().first;
		int y = que.front().second;
		if (make_pair(x, y) != vacuum)
		{
			tab[x][y] = '$';
		}
		int xx = x + vDir[idDir].first;
		int yy = y + vDir[idDir].second;
		if (tab[xx][yy] == '#' || tab[xx][yy] == '$')
		{
			que.push(make_pair(xx, yy));
		}
		else
		{
			for (int idTurn = 0; idTurn < 2; ++idTurn)
			{
				int idDirNew = find_id_dir_new(idDir, idTurn);
				xx = x + vDir[idDirNew].first;
				yy = y + vDir[idDirNew].second;

				if (tab[xx][yy] == '#')
				{
					idDir = idDirNew;
					que.push(make_pair(x, y)); // re-pushing this position so the vacuum can choose a good direction in the next iteration

					if (nSteps) pathFile << nSteps << ",";
					pathFile << vCar[idTurn] << ",";
					nSteps = -1;
					break;
				}
			}
		}
		++nSteps;
		que.pop(); // erasing that position

	}

	--nSteps;
	if (nSteps) pathFile << nSteps;
}

int main()
{

	vector <long long> vProg;
	fParse(vProg);

	//long long input = 0;
	queue< int > inputQue;
	inputQue.push(0);
	vector<long long> vOutputs;
	fRunProgram(inputQue, vProg, vOutputs);
	inputQue.pop();

	vector < string > tab(2);
	fCreateTab(vOutputs, tab);
	fPrintTab(tab);

	int sum = 0;
	fFindSum(sum, tab);

	fout << "part 1: " << sum << "\n";
	cout << "part 1 completed...\n";

	pair <int, int> vacuum;
	fFindVacuum(vacuum, tab);

	fFindPath(tab,vacuum);

	//A,B,A,C,B,C,B,C,A,C (see pathFile.txt and pathFile_with_functions.txt)

	string str{ "A,B,A,C,B,C,B,C,A,C\n" };
	str.append("R,12,L,10,R,12\n");
	str.append("L,8,R,10,R,6\n");
	str.append("R,12,L,10,R,10,L,8\n");
	str.append("n\n");

	for (int iPush = 0; iPush < str.size(); ++iPush)
	{
		inputQue.push(str[iPush]);
	}
	
	vOutputs.clear();
	vProg[0] = 2;
	fRunProgram(inputQue, vProg, vOutputs);

	fout << "part 2: " << vOutputs[vOutputs.size()-1] << "\n";
	cout << "part 2 completed as well !\n";

	return 0;
}