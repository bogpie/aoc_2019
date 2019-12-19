#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

ifstream fin("d07_in.txt");
ofstream fout("d07_out.txt");

struct sctAmp
{
	vector <long long> vProg;
	queue <long long> inputQue;
	long long iProg;
};

void fParse(vector <sctAmp> & vAmps)
{
	long long x;
	char comma;
	while (fin >> x)
	{
		fin >> comma;

		for (long long iAmp = 0; iAmp < 5; ++iAmp)
		{
			vAmps[iAmp].vProg.push_back(x);
		}

		if (comma == '\0')
		{
			break;
		}
	}
	return;
}

void fParseInstruction(long long & opcode, long long instruction, long long vParamMode[])
{
	opcode = instruction % 100;
	long long divide = 100;
	for (long long iParam = 1; iParam <= 3; ++iParam)
	{
		vParamMode[iParam] = instruction / divide % 10;
		divide *= 10;
	}
}



void fFindSingleParameter(vector <long long> vProg, long long iProg, long long vParam[], long long iParam, long long vParamMode[])
{
	long long param = vProg[iProg + iParam];
	long long paramMode = vParamMode[iParam];
	if (paramMode != 1)
	{
		long long position = param;

		if (position < 0 || position >= vProg.size())
		{
			vProg.resize(position + 3, 0);
		}

		if (paramMode == 0)
		{
			param = vProg[param];
		}
	
	}

	vParam[iParam] = param; 
	
}

void fFindParameters(vector <long long> vProg, long long iProg, long long vParam[], long long vParamMode[],long long opcode)
{
	if (opcode != 99 && opcode != 3)
	{
		fFindSingleParameter(vProg, iProg, vParam, 1, vParamMode);
		if (opcode != 4 && opcode != 9)
		{
			fFindSingleParameter(vProg, iProg , vParam, 2, vParamMode);
		}
	}
}


void fPrint(vector <long long> vProg,long long nProg,long long & nSteps)
{
	fout << "After " << nSteps << " nSteps : ";
	++nSteps;


	for (long long iProg = 0; iProg < nProg; ++iProg)
	{
		fout << vProg[iProg] << ' ';
	}
	fout << "\n\n";
}

void fRunProgram(vector <sctAmp> vAmps, long long & finalOutput, long long part)
{
	long long iAmp = 0;
	vector <long long> vProg = vAmps[iAmp].vProg;
	long long iProg = vAmps[iAmp].iProg;
	queue <long long> inputQue = vAmps[iAmp].inputQue;
	while (1)
	{
		long long instruction = vProg[iProg], vParamMode[4], opcode;
		
		fParseInstruction(opcode, instruction, vParamMode);
		
		long long vParam[4];
		fFindParameters(vProg, iProg, vParam, vParamMode,opcode);
		
		switch (opcode)
		{
			case 1:
			{
				long long position3 = vProg[iProg+3];
				vProg[position3] = vParam[1] + vParam[2];
				iProg += 4;
				break;
			}
			case 2:
			{
				
				long long position3 = vProg[iProg+3];		
				vProg[position3] = vParam[1] * vParam[2];
				iProg += 4;
				break;
			}
			case 3:
			{
				if (!inputQue.empty())
				{
					long long position1 = vProg[iProg + 1];
					vProg[position1] = inputQue.front();
					inputQue.pop();
					iProg += 2;
				}
				else
				{
					vAmps[iAmp].inputQue = inputQue;
					vAmps[iAmp].iProg = iProg;
					vAmps[iAmp].vProg = vProg;

					iAmp = (iAmp + 1) % 5;

  					inputQue = vAmps[iAmp].inputQue;
					iProg = vAmps[iAmp].iProg;
					vProg = vAmps[iAmp].vProg;
				}

				break;
			}
			case 4:
			{
 				long long output = vParam[1] ;
				//fout << "Output: " << output << '\n';
				iProg += 2;
						
				vAmps[(iAmp + 1) % 5].inputQue.push(output);

				if (part == 1)
				{
					if (iAmp == 4)
					{
						finalOutput = output;
						return;
					}
					vAmps[iAmp].inputQue = inputQue;
					vAmps[iAmp].iProg = iProg;
					vAmps[iAmp].vProg = vProg;

					iAmp = (iAmp + 1) % 5 ;
					inputQue = vAmps[iAmp].inputQue;
					iProg = vAmps[iAmp].iProg;
					vProg = vAmps[iAmp].vProg;
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
				vProg[position3] = (vParam[1] < vParam[2]);
				iProg += 4;
				break;
			}	
			case 8:
			{
				
				long long position3 = vProg[iProg + 3];
				vProg[position3] = (vParam[1] == vParam[2]);
				iProg += 4;
				break;
			}
		
			case 99:
			{
				//iProg = -1; fout << "Halted !\n\n\n";exit(1); break;
				if (part == 1)
				{
					return;
				}
				else
				{
					if (iAmp == 4)
					{
						inputQue = vAmps[0].inputQue;
						while (!inputQue.empty())
						{
							finalOutput = inputQue.front();
							inputQue.pop();
						}

						return;
					}

					iAmp = (iAmp + 1) % 5;
					inputQue = vAmps[iAmp].inputQue;
					iProg = vAmps[iAmp].iProg;
					vProg = vAmps[iAmp].vProg;

				}
			}
		}
	} 
}

void fProvidePhases(vector <sctAmp> vAmps, vector <long long> vPhases, long long & finalOutput, long long part)
{
	for (long long iAmp = 0; iAmp < 5; ++iAmp)
	{
		vAmps[iAmp].inputQue.push(vPhases[iAmp]);
	}
	vAmps[0].inputQue.push(0);

	//finalOutput = 0;
	fRunProgram(vAmps, finalOutput, part);	
}

void fPart(long long part, vector <sctAmp> vAmps)
{
	long long maxOutput = LLONG_MIN;
	vector <long long> vPhases;

	if (part == 1)
	{
		vPhases = { 0,1,2,3,4 };
	}
	else
	{
		vPhases = { 5,6,7,8,9 };
	}

	do
	{
		if (vPhases[0] == 9 && vPhases[1]==8 && vPhases[2]==7 && vPhases[3] == 6 && vPhases[4] == 5)
		{
			int debug = 1;
		}

		long long finalOutput = 0;
		fProvidePhases(vAmps, vPhases, finalOutput, part);
		if (finalOutput > maxOutput) maxOutput = finalOutput;
	} while (next_permutation(vPhases.begin(), vPhases.end()));

	fout << "part " << part << " : maximum output : " << maxOutput << "\n\n";
}

int main()
{
	vector <sctAmp> vAmps;
	vAmps.resize(6);
	fParse(vAmps);
	
	fPart(1,vAmps);
	fPart(2,vAmps);

	return 0;
}