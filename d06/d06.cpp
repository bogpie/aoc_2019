#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream fin ("d06_in.txt");
ofstream fout ("d06_out.txt");

const int INF = INT_MAX, NNODE = 2000, LGSTR=10;
int vCountOrbits[NNODE];
int vCountSteps[NNODE];
int nObj,iLeft,iRight,iCOM,sum,nAdj,iAdj,iYOU,iSAN,sol,newDist,iReach;

vector <int> vRight[NNODE];
vector <int> vLeft[NNODE];
vector <int> vLine[NNODE];
queue <int> qu;

char arrow[LGSTR],strLeft[LGSTR],strRight[LGSTR];
char vObj[NNODE][LGSTR];

int main()
{
    nObj=0;

    while (fin.getline(arrow,10))
    {
        strcpy(strLeft,arrow);
        strLeft[3]='\0';
        strcpy(strRight,arrow+4);

        iLeft=0,iRight=0;

        for (iLeft=0; iLeft<nObj; ++iLeft)
        {
            if (strcmp(vObj[iLeft],strLeft) == 0)
            {
                break;
            }
        }
        if (iLeft == nObj)
        {
            ++nObj;
            strcpy(vObj[iLeft],strLeft);

        }
        for (iRight=0; iRight<nObj; ++iRight)
        {
            if (strcmp(vObj[iRight],strRight) == 0)
            {
                break;
            }
        }
        if (iRight == nObj)
        {
            ++nObj;
            strcpy(vObj[iRight],strRight);

        }


        vLeft[iRight].push_back(iLeft);
        vRight[iLeft].push_back(iRight);
        vLine[iLeft].push_back(iRight);
        vLine[iRight].push_back(iLeft);
        //vRight[iRight].push_back(iRight);
    }


    iCOM = 0;
    for (iCOM=0; iCOM<nObj; ++iCOM)
    {
        if (!strcmp("COM",vObj[iCOM]))
        {
            break;
        }
    }

    qu.push(iCOM);


    sum =0;
    while (!qu.empty())
    {
        iLeft = qu.front();
        nAdj = vRight[iLeft].size();

        for ( iAdj=0; iAdj<nAdj; ++iAdj)
        {
            iRight = vRight[iLeft][iAdj];
            qu.push(iRight);
            vCountOrbits[iRight] = vCountOrbits[iLeft] + 1;
            sum += vCountOrbits[iRight];
        }

        qu.pop();

    }

    fout << "Part 1: " << sum << '\n';


    iYOU=0,iSAN=0;
    for (iYOU = 0 ; iYOU < nObj ; ++iYOU)
    {
        if (!strcmp("YOU",vObj[iYOU]))
        {
            break;
        }
    }

    for (iSAN = 0 ; iSAN < nObj ; ++iSAN)
    {
        if (!strcmp("SAN",vObj[iSAN]))
        {
            break;
        }
    }


    for ( iLeft=0; iLeft<1999; ++iLeft)
    {
        vCountSteps[iLeft]=INT_MAX;
    }

    sol = INT_MAX;

    while (!qu.empty())
    {
        qu.pop();
    }

    iLeft = vLeft[iYOU][0];
    iReach = vLeft[iSAN][0];

    qu.push(iLeft);
    vCountSteps[iLeft]=0;

    while (!qu.empty())
    {
        iLeft = qu.front();
        nAdj = vLine[iLeft].size();
        for ( iAdj=0; iAdj<nAdj; ++iAdj)
        {
            iRight = vLine[iLeft][iAdj];
            newDist = vCountSteps[iLeft] + 1;

            if (newDist < vCountSteps[iRight])
            {
                vCountSteps[iRight]=newDist;
                qu.push(iRight);
            }
        }
        qu.pop();
    }

    sol = vCountSteps[iReach];

    fout << "Part 2 : " << sol;
    /// sol == vCountSteps[iSAN] - 1;

    return 0;
}
