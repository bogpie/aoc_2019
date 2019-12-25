#include <fstream>
#include <queue>
#include <vector>

using namespace std;

ifstream fin("d25_in.txt");
ofstream fout("d25_out.txt");

typedef vector<long long> Program;
typedef pair < Program, long long> State;

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

void fRunProgram(queue <long long> inputQue, vector <long long> vProg,long long & iProg,long long & relBase,vector <char> & vOutputs)
{
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

			vProg[position1] = inputQue.front(); inputQue.pop();

			if (inputQue.empty())
			{
				string str("south\n");
				for (int iPush = 0; iPush < str.size(); ++iPush)
				{
					inputQue.push(str[iPush]);
				}
			}
			
			iProg += 2;
			break;
		}
		case 4:
		{
			long long output = vParam[1];
			char outputChar = (char)output;
			
			//fout << outputChar;
			vOutputs.push_back(outputChar);
			
			if (vOutputs.size() >= 10000)
			{
				return;
			}

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
		default:
		{
			fout << "wrong opcode!\n";
			exit(1);
		}
		}
	}
}


int main()
{
	vector <long long> vProg;
	fParse(vProg);

	queue <long long> inputQue;
	string str("east\n");
	for (int iPush = 0; iPush < str.size(); ++iPush)
	{
		inputQue.push(str[iPush]);
	}
	vector < char > vOutputs;

	queue <State> que;
	State state = make_pair(vProg, 0);

	que.push(state);

	vector<string> vStr;
	vStr[0].push_back("north");
	vStr[1].push_back("south");
	vStr[2].push_back("west");
	vStr[3].push_back("east");

	while (!que.empty())
	{
		for (int iDir = 0; iDir < 4; ++iDir)
		{
			string str;
			str.append(vStr[iDir]);
			for (int iPush = 0; iPush < str.size(); ++iPush)
			{
				inputQue.push(str[iPush]);
			}
			fRunProgram(inputQue, vProg, iProg,relBase,vOutputs);
			
		}
	}

	
	for (int iOutput = 0; iOutput < vOutputs.size(); ++iOutput)
	{
		fout << vOutputs[iOutput];
	}

	return 0;
}