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
typedef pair < Point, int > Queued;
typedef char Node;
typedef pair < Node, int > Edge;
typedef tuple < int, int, Node, vector <bool> > State;

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
	que.push(make_pair(point, 0));
	while (!que.empty())
	{
		Queued queued = que.front();
		Point point = queued.first;
		int x = point.first;
		int y = point.second;
		int nSteps = queued.second ;
		for (int idDir = 0; idDir < 4; ++idDir)
		{
			int xx = x + vDir[idDir].first;
			int yy = y + vDir[idDir].second;
			
			if (tab[xx][yy] == '#')
			{
				continue;
			}
			if (tab[xx][yy] == '.' )
			{
				Point newPoint = make_pair(xx, yy);
				que.push(make_pair(newPoint,nSteps+1));
			}
			//if (isKey(tab[xx][yy]) || isDoor(tab[xx][yy]) || tab[xx][yy] == '@');
			else
			{
				char newCar = tab[xx][yy];
				
				if (nSteps+1 >= vLength[car][newCar])
				{
					continue;
				}

				vLength[car][newCar] = vLength[newCar][car] = nSteps + 1;
	
				Edge edge = make_pair(newCar, nSteps + 1);
				vEdges[car].push_back(edge);

				if (car == '@') continue;

				edge = make_pair(car, nSteps + 1);
				vEdges[newCar].push_back(edge);

			}
			
		}

		tab[x][y] = '#';
		que.pop();
	}
}

void dijkstra(char node, vector < vector < Edge > > vEdges, int nKeys, int & ans)
{
	ans = INF;
	vector < int > vDist(128);

	for (int i = 0; i < 128; ++i)
	{
		vDist[i] = INF;
	}

	vDist[node] = 0;

	vector < bool > hasKey(128);
	State state = make_tuple(0,nKeys,'@',hasKey);
	set < State > pri;
	pri.insert(state);

	while (!pri.empty())
	{
		
		State state = *pri.begin();

		pri.erase(pri.begin());
		
		int dist = get<0>(state);
		int nRem = get<1>(state);
		Node node = get<2>(state);
		auto hasKey = get<3>(state);

		if (nRem==0)
		{
			if (vDist[node] < ans)
			{
				ans = vDist[node];
			}
		}

		for (int iNeighb = 0; iNeighb < vEdges[node].size(); ++iNeighb)
		{
			Edge edge = vEdges[node][iNeighb];
			Node neighb = edge.first;
			int add = edge.second;
			int newDist = dist + add;
			if ( newDist < vDist[neighb])
			{
				if (isDoor(neighb))
				{
					if (!hasKey[neighb])
					{
						continue;
					}
				}
				else if (isKey(neighb))
				{
					char door = neighb - ('a' - 'A');
					hasKey[door] = 1;
					--nRem;
				}


				State newState=make_tuple(newDist,nRem,neighb,hasKey);
				vDist[neighb] = newDist;
				pri.insert(newState);
			}

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
			if (car != '.' && car!='#')
			{
				if (isKey(car))
				{
					++nKeys;
				}
				Point point = make_pair(iTall, iWide);
				bfs(tab, point, vEdges,vLength);
			}
		}
	}

	
	int ans = INF;
	dijkstra('@',vEdges,nKeys,ans);
	fout << "part 1: " << ans << "\n";
	return 0;
}