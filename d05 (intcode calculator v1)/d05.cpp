#include <fstream>
#include <vector>

using namespace std;

ifstream fin("d05_in.txt");
ofstream fout("d05_out.txt");

void fParse(vector <long long> & vProg)
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

void fRunProgram(long long input, vector <long long> vProg)
{
	long long iProg = 0;
	long long nSteps = 0;

	
	while (iProg >= 0)
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
				long long position1 = vProg[iProg+1];
				vProg[position1] = input;
				iProg += 2;
				break;
			}
			case 4:
			{
 				long long output = vParam[1] ;
				if (output)
				{
					fout << "Needed ";
				}
				fout << "output: " << output << '\n';
				
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
				fout << "Halted !\n\n\n";
				iProg = -1;
				//exit(1);
				break;
				return;
			}
		}
	} 
}


int main()
{
	vector <long long> vProg;
	fParse(vProg);
	
	long long input; 

	input = 1;
	fout << "input " << input << ": \n";
	fRunProgram(input, vProg);
	
	
	input = 5;
	fout << "input " << input << ": \n";
	fRunProgram(input, vProg);

	return 0;
}