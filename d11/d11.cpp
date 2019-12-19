#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

ifstream fin("d11_in.txt");
ofstream fout("d11_out.txt");

void fParse( vector <long long> & vProg)
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



void fFindSingleParameter(vector <long long> vProg, long long iProg, long long vParam[], long long iParam, long long vParamMode[], long long relBase)
{
	long long param = vProg[iProg + iParam];
	long long paramMode = vParamMode[iParam];
	if (paramMode != 1)
	{
		long long position = param + (paramMode == 2) * relBase;

		if (position < 0)
		{
			int debug = 1;
		}

		if (position >= vProg.size())
		{
			vProg.resize(position + 3, 0);
		}
		else if (position < 0)
		{
			fout << "Negative position !";
			exit(1);
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

void fFindParameters(vector <long long> vProg, long long iProg, long long vParam[], long long vParamMode[], long long opcode, long long relBase)
{
	if (opcode != 99 && opcode != 3)
	{
		fFindSingleParameter(vProg, iProg, vParam, 1, vParamMode, relBase);
		if (opcode != 4 && opcode != 9)
		{
			fFindSingleParameter(vProg, iProg, vParam, 2, vParamMode, relBase);
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

void fRunProgram(long long input, vector <long long> & vProg, long long & iProg, queue <long long > & vOutputs,long long & relBase)
{
	while (iProg >= 0)
	{
		if (iProg > vProg.size()) vProg.resize(iProg + 4, 0);
		long long instruction = vProg[iProg], vParamMode[4], opcode;
		fParseInstruction(opcode, instruction, vParamMode);

		long long vParam[4];
		fFindParameters(vProg, iProg, vParam, vParamMode, opcode, relBase);

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
			long long output = vParam[1];
			//fout << "Output: " << output << '\n';
			vOutputs.push(output);
			
			iProg += 2;
			if (vOutputs.size() == 2)
			{
				return;
			}
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

void findDirection(pair <long long, long long> & direction, long long turn)
{
	//N
	if (direction.first == -1 && direction.second == 0)
	{
		if (turn == 0) direction = make_pair(0,-1);
		else direction = make_pair(0,1);
	}

	//S
	else if (direction.first == 1 && direction.second == 0)
	{
		if (turn == 0)  direction = make_pair(0, 1); 
		else direction = make_pair(0, -1);
	}

	//E
	else if (direction.first == 0 && direction.second == 1)
	{
		if (turn == 0) direction = make_pair(-1,0);
		else direction = make_pair(1,0);
	}
	
	//V
	else if (direction.first == 0 && direction.second == -1)
	{
		if (turn == 0) direction = make_pair(1,0);
		else direction = make_pair(-1,0);
	}
}

void fPart(long long part,vector <long long> vProg, map < pair <long long, long long >, long long > mapPoints)
{
	long long x = 0, y = 0, iProg = 0;
	queue <long long> vOutputs;

	pair <long long, long long > direction = make_pair(-1, 0);

	long long relBase = 0;
	while (1)
	{
		long long turn, color = part - 1;

		pair < long long, long long > pairPoint = make_pair(x, y);

		if (mapPoints.find(pairPoint) != mapPoints.end())
		{
			color = mapPoints[pairPoint];
		}


		if (part == 2 && mapPoints.size() == 2)
		{
			int debug = 1;
		}

		fRunProgram(color, vProg, iProg, vOutputs,relBase);

		if (!vOutputs.empty())
		{
			color = vOutputs.front();
			vOutputs.pop();
		}
		else break;

		turn = -1;
		if (!vOutputs.empty())
		{
			turn = vOutputs.front();
			vOutputs.pop();
		}

		mapPoints[pairPoint] = color;

		if (iProg == -1) break;
		if (turn == -1) break;

		findDirection(direction, turn);

		//fout << x << " " << y << " " << turn << "\n";

		x += direction.first;
		y += direction.second;

	}

	fout << "part " << part << ":\n";
	
	if (part == 1)
	{
		fout  << mapPoints.size() << "\n";
	}
	else
	{
		pair <long long, long long > pairPoint  = mapPoints.begin()->first;
		long long xMin = pairPoint.first;
		long long yMin = pairPoint.second;		
		
		map<pair<long long, long long>, long long>::iterator it;
		it = mapPoints.end();
		--it;
		pairPoint  = it->first;
		long long xMax = pairPoint.first;
		long long yMax = pairPoint.second;

		x = 0;
		y = 0;
		for (x = xMin; x <= xMax; ++x)
		{
			for (y = yMin; y <= yMax; ++y)
			{
				pairPoint = make_pair(x, y);
				long long color = 0;
				if (mapPoints.find(pairPoint)!=mapPoints.end())
				{
					color = mapPoints[pairPoint];
				}
				if (color)
				{
					fout << " # ";
				}
				else fout << "   ";
			}
			fout << "\n";
		}
		int debug = 1;
	}


}

int main()
{

	
	vector <long long> vProg;
	fParse(vProg);
	map < pair <long long , long long > , long long > mapPoints;

	fPart(1,vProg,mapPoints);
	fPart(2,vProg,mapPoints);


	return 0;
}

