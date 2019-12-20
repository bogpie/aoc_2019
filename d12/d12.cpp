#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

ifstream fin("d12_in.txt");
ofstream fout("d12_out.txt");

struct sctPoint
{
	long long vPos[3];
	long long vVel[3]; 
};

void fSctCpy(vector <sctPoint> & vPointsBak, vector <sctPoint> vPoints)
{
	for (int iCoord = 0; iCoord < 3; ++iCoord)
	{
		for (int iPoint = 0; iPoint < 4; ++iPoint)
		{
			vPointsBak[iPoint].vPos[iCoord] = vPoints[iPoint].vPos[iCoord];
			vPointsBak[iPoint].vPos[iCoord] = vPoints[iPoint].vPos[iCoord];
		}
	}
}


void fParse(vector <sctPoint> & vPoints)
{
	int iPoint = 1;
	char chr;

	for (int iPoint = 0 ; iPoint <4 ;	++iPoint )
	{
		vPoints[iPoint].vVel[0] = vPoints[iPoint].vVel[1] = vPoints[iPoint].vVel[2]= 0;
		
		fin >> chr >> chr >> chr;		//<x=
		fin >> vPoints[iPoint].vPos[0]; //-8
		fin >> chr >> chr >> chr ;		//,y=
		fin >> vPoints[iPoint].vPos[1]; //-10
		fin >> chr >> chr >> chr;		//,_z=
		fin >> vPoints[iPoint].vPos[2]; //0
		fin >> chr;						//>

	
	}
}

void fRecalculatePos(vector <sctPoint> & vPoints)
{
	for (int iCoord = 0; iCoord < 3; ++iCoord)
	{
		for (int iPoint = 0; iPoint < 4; ++iPoint)
		{
			vPoints[iPoint].vPos[iCoord] += vPoints[iPoint].vVel[iCoord];
		}
	}
}
void fRecalculateVel(vector <sctPoint> & vPoints)
{
	for (int iCoord = 0; iCoord < 3; ++iCoord)
	{
		for (int iPoint = 0; iPoint < 4; ++iPoint)
		{
			for (int jPoint = iPoint + 1; jPoint < 4; ++jPoint)
			{
				if (vPoints[iPoint].vPos[iCoord] < vPoints[jPoint].vPos[iCoord])
				{
					vPoints[iPoint].vVel[iCoord]++;
					vPoints[jPoint].vVel[iCoord]--;
				}
				else if (vPoints[iPoint].vPos[iCoord] > vPoints[jPoint].vPos[iCoord])
				{
					vPoints[iPoint].vVel[iCoord]--;
					vPoints[jPoint].vVel[iCoord]++;
				}
			}
		}
	}
}

void fCalculateEnergy(vector <sctPoint> vPoints, long long & sum)
{
	sum = 0;
	for (int iPoint = 0; iPoint < 4; ++iPoint)
	{
		long long pot = 0;
		long long kin = 0;
		//long long total = 0;
		for (int iCoord = 0; iCoord < 3; ++iCoord)
		{
			pot += abs(vPoints[iPoint].vPos[iCoord]);
			kin += abs(vPoints[iPoint].vVel[iCoord]);
		}
		sum += pot * kin;
	}
}

bool fSctCmpCoord(vector <sctPoint> vPoints, vector <sctPoint> vPointsBak,int coordInvestigated)
{
	//for (int iCoord = 0; iCoord < 3; ++iCoord)

	int iCoord = coordInvestigated;
	{
		for (int iPoint = 0; iPoint < 3; ++iPoint)
		{
			if (vPoints[iPoint].vPos[iCoord] != vPointsBak[iPoint].vPos[iCoord]) return 0;
			if (vPoints[iPoint].vVel[iCoord] != vPointsBak[iPoint].vVel[iCoord]) return 0;
		}
	}
	return 1;
}

void fSimulate(vector <sctPoint> vPoints, vector <sctPoint> vPointsBak, long long & nSteps,long long & sum,int coordInvestigated, int part)
{
	long long iStep = 0;
	while (1)
	{
		fRecalculatePos(vPoints);

		if (part == 1)
		{
			if (iStep == nSteps) break;
		}
		else
		{
			if (fSctCmpCoord(vPoints, vPointsBak,coordInvestigated) && iStep)
			{
				nSteps = iStep;
				break;
			}
		}
		fRecalculateVel(vPoints);

		++iStep;
	}
	sum = 0;
	fCalculateEnergy(vPoints, sum);
}

void fCalculateLcm(long long a, long long b, long long & lcm)
{
	long long prod = a * b;
	while (b)
	{
		long long aux_a = a;
		a = b;
		b = aux_a % b;
	}
	lcm = prod / a;
}

void fPart1(vector < sctPoint > vPoints)
{
	long long nSteps = 1000;
	long long sum = 0;
	fSimulate(vPoints, vPoints, nSteps, sum, -1, 1);
	fout << "part 1: " << sum << "\n";
}

void fPart2(vector < sctPoint > vPoints)
{
	long long vSteps[3];
	long long sum = 0;

	fSimulate(vPoints, vPoints, vSteps[0], sum, 0, 2);
	fSimulate(vPoints, vPoints, vSteps[1], sum, 1, 2);
	fSimulate(vPoints, vPoints, vSteps[2], sum, 2, 2);

	long long lcm = 0;
	fCalculateLcm(vSteps[0], vSteps[1], lcm);
	fCalculateLcm(lcm, vSteps[2], lcm);

	fout << "part 2: " << lcm << "\n";
}

int main()
{
	vector <sctPoint> vPoints; 	vPoints.resize(4);
	
	cout << "seconds...\n";
	
	fParse(vPoints);

	fPart1(vPoints);
	fPart2(vPoints);

	return 0;
}
