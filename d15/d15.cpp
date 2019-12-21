#include <fstream>
#include <tuple>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream fin("d15_in.txt");
ofstream fout("d15_out.txt");


typedef tuple < vector < long long > , long long , long long , long long , long long > State;
typedef pair <long long, long long > Point;
typedef tuple < Point, State, long long > QueElem;

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

void fRunProgram(State & state)
{
	vector <long long> vProg = get<0>(state);
	long long iProg = get<1>(state);
	long long relBase = get<2>(state);
	long long input = get<3>(state);
	long long output = get<4>(state);


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
			iProg += 2;
			state = make_tuple(vProg, iProg, relBase, input, output);
			return;
			//fout << "Output: " << output << '\n';
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
			state = make_tuple(vProg, iProg, relBase, input, 0);
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

void lee( QueElem elem,long long & answer,Point & oxygenPoint,State & oxygenState)
{
	auto point = get<0>(elem);
	auto state = get<1>(elem);
	auto nSteps = get<2>(elem);

	queue<QueElem> que;
	que.push(elem);
	bool found = 0;
	set < Point > visited;
	visited.insert(point);

	while (!que.empty() && !found)
	{
		point = get<0>(que.front());
		state = get<1>(que.front());
		nSteps = get<2>(que.front());

		auto old_state = state;

		for (int idDir = 1; idDir <= 4; ++idDir)
		{
			auto newPoint = findNeighbour(point, idDir);
			if (visited.find(newPoint) != visited.end())
			{
				continue;
			}
			get<3>(state) = idDir;
			fRunProgram(state);

			auto output = get<4>(state);

			if (output == 1)
			{
				que.push(make_tuple(newPoint, state, nSteps + 1));
				visited.insert(newPoint);
			}
			else if (output == 2)
			{
				found = 1;
				oxygenPoint = point;
				oxygenState = state;
				answer = nSteps;
				break;
			}

			state = old_state;

		}
		que.pop();
	}

	if (!found) // for part 2 
	{
		answer = nSteps;
	}
}

int main()
{
	vector <long long> vProg;
	fParse(vProg);

	Point point(0, 0);
	long long iProg = 0, relBase = 0, input = 0, output = 0;
	State state=make_tuple(vProg,iProg,relBase,input,output);

	long long nSteps = 1;
	auto elem = make_tuple(point, state, nSteps);
	long long answer;
	State oxygenState;
	Point oxygenPoint;
	lee(elem,answer,oxygenPoint,oxygenState);
	fout << "part 1: " << answer << " steps to oxygen system \n";
	
	nSteps = 0;
	elem = make_tuple(oxygenPoint, oxygenState, nSteps);
	answer = 0;
	lee(elem, answer, oxygenPoint, oxygenState);
	fout << "part 2: " << answer << " minutes to fill the area \n";

	return 0;
}