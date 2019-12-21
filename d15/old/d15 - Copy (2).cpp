#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream fin("d15_in.txt");
ofstream fout("d15_out.txt");



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


void fPrint(vector <long long> vProg, long long nProg, long long& steps)
{
	fout << "After " << steps << " steps : ";
	++steps;


	for (long long iProg = 0; iProg < nProg; ++iProg)
	{
		fout << vProg[iProg] << ' ';
	}
	fout << "\n\n";
}

void fRunProgram(long long input, vector <long long> & vProg,long long & iProg, long long & relBase, long long & output)
{


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

			vProg[position1] = input;
			iProg += 2;
			break;
		}
		case 4:
		{
			//long long 
			output = vParam[1];
			return;
			//fout << "Output: " << output << '\n';
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
			fout << "Halted !\n";
			iProg = -1;
			//exit(1);
			break;
			return;
		}
		}
	}
}

pair <long long, long long > findNeighbour(pair <long long , long long > point, long long idDir)
{
	if (idDir == 1) //n
	{
		return make_pair(point.first - 1, point.second);
	}
	if (idDir == 2) //s
	{
		return make_pair(point.first + 1, point.second);
	}
	if (idDir == 3) //w
	{
		return make_pair(point.first, point.second-1);
	}
	if (idDir == 4) //w
	{
		return make_pair(point.first, point.second+1);
	}
}


void fStretch(pair <long long , long long > & point , set < pair < long long, long long > > & visited, vector <long long> & vProg, long long &iProg, long long & relBase, long long & nSteps, bool & found)
{
	if (found)
	{
		return;
	}
	for (long long idDir = 1; idDir <= 4; ++idDir)
	{
		long long output;

		long long old_iProg = iProg;
		auto old_vProg = vProg;
		auto old_relBase = relBase;
		fRunProgram(idDir, vProg,iProg,relBase,output);

		if (output == 1)
		{
			
			auto newPoint = findNeighbour(point, idDir);
			if (visited.find(newPoint) != visited.end())
			{
				break;
			}
			++nSteps;
		
			visited.insert(newPoint);
			fStretch(newPoint, visited, vProg, iProg, relBase, nSteps, found);
			visited.erase(visited.find(newPoint));
			--nSteps;
		}
		else if (output == 2)
		{
			found = 1;
			return;
		}
		vProg = old_vProg;
		iProg = old_iProg;
		relBase = old_relBase;

	}
	
}

int main()
{
	vector <long long> vProg;
	fParse(vProg);
	set < pair < long long, long long > > visited;
	pair <long long , long long > point(0,0);
	visited.insert(point);

	queue < pair < long long, long long > > que;
	que.push(point);

	bool found = 0;
	long long nSteps = 0, relBase = 0,iProg=0;

	fStretch(point, visited, vProg,iProg,relBase,nSteps, found);

	fout << "part 1: " << nSteps << "\n";
	
	return 0;
}