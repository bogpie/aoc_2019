#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <set>
#include <tuple>

using namespace std;

ifstream fin("d18_in.txt");
ofstream fout("d18_out.txt");

typedef pair < int, int > Point;
typedef vector < string > Matrix;
typedef vector < char > Obstacles;
typedef tuple < Point, int, Obstacles > Queued;
typedef char Node;
typedef tuple < Node, int, int> Edge;
typedef tuple < int, Node, int > State;

vector < Point >vDir{ make_pair(-1,0),make_pair(1,0),make_pair(0,-1),make_pair(0,+1) };

const int INF = INT_MAX;

bool isDoor(char car)
{
	if (car >= 'A' && car <= 'Z')
	{
		return 1;
	}
	return 0;
}

bool isKey(char car)
{
	if (car >= 'a' && car <= 'z')
	{
		return 1;
	}
	return 0;
}

void bfs(Matrix tab,Point point,vector < vector < Edge > > & vEdges,int vLength[128][128])
{
	queue <Queued> que;

	char car = tab[point.first][point.second];
	
	//int nSteps = 0;
	Obstacles obstacles;
	que.push(make_tuple(point, 0, obstacles));
	while (!que.empty())
	{
		Queued queued = que.front();
		Point point = get<0>(queued);
		int nSteps = get<1>(queued);
		int bitmask = get<2>(queued);
		
		int x = point.first;
		int y = point.second;
		for (int idDir = 0; idDir < 4; ++idDir)
		{
			int xx = x + vDir[idDir].first;
			int yy = y + vDir[idDir].second;
			char newCar = tab[xx][yy];
			if (newCar == '#')
			{
				continue;
			}

			Point newPoint = make_pair(xx, yy);

			if (isDoor(newCar))
			{
				obstacles.push_back(newCar);
			}
			else if (isKey(newCar))
			{				
				if (nSteps+1 >= vLength[car][newCar])
				{
					continue;
				}

				vLength[car][newCar] = vLength[newCar][car] = nSteps + 1;
	
				Edge edge = make_tuple(newCar, nSteps + 1,obstacles);
				vEdges[car].push_back(edge);

				if (car == '@') continue;

				edge = make_tuple(car, nSteps + 1,obstacles);
				vEdges[newCar].push_back(edge);

			}

			que.push(make_tuple(newPoint, nSteps + 1, obstacles));

		}

		tab[x][y] = '#';
		que.pop();
	}
}

void dijkstra(char node, vector < vector < Edge > > vEdges, int nKeys,int & ans)
{

	int bitmask = 0;
	State state = make_tuple (0, '@',bitmask);
	set < State > pri;

	int ret = 1;


	pri.insert(state);

	while (!pri.empty())
	{
		State state = *pri.begin();
		
		//int nRem = get<0>(state);
		int dist = get<0>(state);
		Node node = get<1>(state);
		auto bitmask= get<2>(state);

		if (bitmask == (1 << 27 - 1))
		{
			return;
		}

		pri.erase(pri.begin());

		for (int iNeighb = 0; iNeighb < vEdges[node].size(); ++iNeighb)
		{
			Edge edge = vEdges[node][iNeighb];
			
			Node neighb = get<0>(edge);
			int add = get<1>(edge);
			Obstacles obstacles = get<2>(edge);

			bool locked = 0;
			
			if (locked) continue;

			int newDist = dist + add;	


			char door = neighb - ('a' - 'A');
			
			bool old_hasKey_door = hasKey[door];
			hasKey[door] = 1;
			State newState=make_tuple(newDist,neighb,hasKey);
			pri.insert(newState);
			hasKey[door] = old_hasKey_door;

		}
	}


}

int main()
{
	Matrix tab;
	string str;

	while (fin >> str)
	{
		tab.push_back(str);
	}

	vector < vector < Edge > > vEdges(128);
	
	int vLength[128][128];

	for (int i = 0; i < 128; ++i)
	{
		for (int j = 0; j < 128; ++j)
		{
			vLength[i][j] = INF;
		}
	}

	Point pointStart;

	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		for (int iWide = 0; iWide < tab[iTall].size(); ++iWide)
		{
			char car = tab[iTall][iWide];
			if (car == '@')
			{
				pointStart = make_pair(iTall, iWide);
				break;
			}
		}
		if (pointStart.first) break;
	}

	bfs(tab, pointStart, vEdges, vLength);
	tab[pointStart.first][pointStart.second] = '.';

	int nKeys = 0;
	for (int iTall = 0; iTall < tab.size(); ++iTall)
	{
		for (int iWide = 0; iWide < tab[iTall].size(); ++iWide)
		{
			char car = tab[iTall][iWide];
			if (!isKey(car))
			{
				continue;
			}
			++nKeys;
			Point point = make_pair(iTall, iWide);
			bfs(tab, point, vEdges,vLength);
			
		}
	}

	

	int ans = INF;
	dijkstra('@',vEdges,nKeys,ans);



	fout << "part 1: " << ans << "\n";
	return 0;
}