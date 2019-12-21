#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include "d10.h"
#define PI 3.14

using namespace std;

ifstream fin("d10_in.txt");
ofstream fout("d10_out.txt");

void fParse(vector < pair < int , int > > & vAsteroids)
{
	string line;
	string::iterator itStr;
	int x = 0;
	while (getline(fin, line))
	{
		int y = -1;
		while (1)
		{
			y = line.find("#", y + 1);
			if (y == -1)
			{
				break;
			}
			vAsteroids.push_back({ x,y });
		}
		++x;
	}
}


int findLengthSquared(int x1, int y1, int x2, int y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int findDeterminant(int xA, int yA, int xB, int yB, int xTop, int yTop)
{
	return ((xB - xA) * (yTop - yA) - (yB - yA) * (xTop - xA));
}


double findAngle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int d12 = findLengthSquared(x1, y1, x2, y2);
	int d13 = findLengthSquared(x1, y1, x3, y3);
	int d23 = findLengthSquared(x2, y2, x3, y3);

	double cos = 1L * (d13 + d23 - d12) / (2 * sqrt(d13 * d23));

	double angle = acos(cos) * 180 / PI;

	///  2 vs 13 (left // right)
	int xTop = x2, yTop = y2;
	double determinant = findDeterminant(x1, y1, x3, y3, xTop, yTop);
	if (determinant < 0) angle = 360 - angle;

	return angle;
}


void findSetAngle(int x3,int y3,set < int > & setAngle, vector < pair <int,int> >  vAsteroids)
{
	for (int i2 = 0; i2 < vAsteroids.size(); ++i2)
	{
		if (x3 == vAsteroids[i2].first && y3==vAsteroids[i2].second) continue;

		int x2 = vAsteroids[i2].first;
		int y2 = vAsteroids[i2].second;

		int x1 = x3 - 1;
		int y1 = y3;

		double angle = findAngle(x1, y1, x2, y2, x3, y3);
		int angleAprox = (int)(angle * 10);

		setAngle.insert(angleAprox);

		int debug = 1;
	}
}

void fDraw(pair < int, int > station, vector < set < pair < int, pair < int, int > > > >& vLines, vector < pair < int, int > > vAsteroids)
{
	int x3 = station.first;
	int y3 = station.second;

	for (int i2 = 0; i2 < vAsteroids.size(); ++i2)
	{
		int x2 = vAsteroids[i2].first;
		int y2 = vAsteroids[i2].second;

		if (x2 == station.first && y2 == station.second)
		{
			continue;
		}

		int x1 = x3 - 1;
		int y1 = y3;
		double angle = findAngle(x1, y1, x2, y2, x3, y3);
		int angleAprox = (int)(angle * 10);

		int manhattan = abs(x2 - x3) + abs(y2 - y3);
		pair < int, int > asteroid = { x2,y2 };
		pair < int, int > pairCoord = make_pair(x2, y2);
		pair < int, pair < int, int > > pairAsteroid = make_pair(manhattan, pairCoord);

		vLines[angleAprox].insert(pairAsteroid);
	}
}

void findBest(vector< pair<int, int> > vAsteroids, int & maxDetected,pair <int , int >  & station )
{
	maxDetected=-1;  
	for (int i3 = 0; i3 < vAsteroids.size(); ++i3)
	{
		set <int> setAngle;
		//setAngle.clear();
		int x3 = vAsteroids[i3].first;
		int y3 = vAsteroids[i3].second;

		findSetAngle(x3,y3,setAngle,vAsteroids);

		int nDetected = setAngle.size();
		if (nDetected > maxDetected)
		{
			maxDetected = nDetected;
			station = { x3,y3 };
		}

	}

}



void fVaporize(pair < int , int > station, int & y0x, vector < pair < int , int > > vAsteroids) // vaporize 200 
{
	vector < set < pair < int, pair <int, int > > > > vLines(3601);
	fDraw(station, vLines, vAsteroids);
	set < int > setAngle;
	set < int >::iterator it;

	findSetAngle(station.first, station.second, setAngle, vAsteroids);
		
	it = setAngle.begin();

	int nVaporized = 0;

	while (1)
	{
		int angleApprox = *it;

		if (nVaporized + 1 == 200)
		{
			pair <int , int > pairAsteroid = vLines[angleApprox].begin()->second;
			y0x = pairAsteroid.second * 100 + pairAsteroid.first;
			break;
		}

		vLines[angleApprox].erase(vLines[angleApprox].begin());
		++nVaporized;

		if (vLines[angleApprox].empty())
		{
			set < int >::iterator itAux = it ;
			++itAux;
			setAngle.erase(it);
			it = itAux;
		}
		else
		{
			++it;
		}


		if (it == setAngle.end())
		{
			it = setAngle.begin();
		}
	}
}

int main()
{
	vector < pair < int , int > > vAsteroids;
	fParse(vAsteroids);


	int maxDetected;
	pair < int , int > station;
	findBest(vAsteroids,maxDetected,station);
	fout << "part 1 : " << maxDetected <<" detected, w/ asteroid-station : { " << station.second << " , " << station.first << " } \n" ;

	int y0x;
	fVaporize(station, y0x,vAsteroids); // vaporize 200 
	fout << "part 2 : " << y0x << " = coord2 * 100 + coord1 \n";

	return 0;
}



/*   
			  2'
		1	
		|>>>>>>2
		|>>>>//
		|>>>//
		V>>//
	       (3)
*/
