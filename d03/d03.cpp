#include <fstream>
#include <set>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

ifstream fin ("d03.in");
ofstream fout("d03.out");

struct sctpoint
{
    int x;
    int y;
};

struct sctline
{
    sctpoint point1;
    sctpoint point2;
};

const int NWIRES=2;
int xcrt,ycrt;


vector <sctpoint> vcross;
vector <sctline> vlines[3];
pair < int, int > per;
set < pair <int, int > > vnodes;
set < pair <int, int > >::iterator it;

int main ()
{
    int nsteps = 0,ncross = 0;

    //long long tab[1000][1000];
    char dircode,comma;
    sctpoint vdir[260];


    vdir['U'] = {-1, 0};
    vdir['D'] = {+1, 0};
    vdir['R'] = { 0,+1};
    vdir['L'] = { 0,-1};

    // dircode ='\0';

    int nextwire = 0;

    for (int iwire=0; iwire<2; ++iwire)
    {
        xcrt=0;
        ycrt=0;

        while (1)
        {
            if (!nextwire)
            {
                fin >> dircode ;
            }
            else
            {
                nextwire=0;
            }
            fin >> nsteps >> comma;

            int xnew = xcrt + vdir[dircode].x * nsteps;
            int ynew = ycrt + vdir[dircode].y * nsteps;

            sctpoint point1= {xcrt,ycrt};
            sctpoint point2= {xnew,ynew};

            vlines[iwire].push_back({point1,point2});

            while (nsteps)
            {
                --nsteps;
                xcrt += vdir[dircode].x;
                ycrt += vdir[dircode].y;
                //++tab[xcrt][ycrt];

                it = vnodes.find( make_pair ( xcrt, ycrt ) );


                if (iwire == 0)
                {
                    if ( (xcrt!=0 || ycrt!=0) )
                    {
                        vnodes.insert( make_pair ( xcrt, ycrt ) );
                    }

                }
                else
                {
                    if ( it != vnodes.end())
                    {
                        vcross.push_back({xcrt,ycrt});
                    }
                }
            }
            if (comma != ',' || fin.eof())
            {
                dircode = comma;
                nextwire=1;
                break;
            }

        }

    }

    ncross = vcross.size();
    int mndist = abs(vcross[0].x) + abs(vcross[0].y);
    for (int icross=1; icross<ncross; ++icross)
    {
        sctpoint point = vcross[icross];
        int dist = abs(point.x)+abs(point.y);
        if (dist < mndist)
        {
            mndist = dist;
        }
    }

    fout << "part 1: " << mndist << '\n';

    int nstepsmin = INT_MAX;

    for (int icross=1;icross<ncross;++icross)
    {
        sctpoint point = vcross[icross];

        int xcross = vcross[icross].x;
        int ycross = vcross[icross].y;

        int nlines1 = vlines[0].size();
        int nsteps1 = 0;
        for (int ilines = 0 ; ilines < nlines1 ; ++ilines)
        {
            int xcrt = vlines[0][ilines].point1.x;
            int xnew = vlines[0][ilines].point2.x;
            int ycrt = vlines[0][ilines].point1.y;
            int ynew = vlines[0][ilines].point2.y;

            if (xcrt == xnew && xcrt == xcross)
            {
                nsteps1 += abs(ycross - ycrt);
                break;
            }
            else if (ycrt == ynew && ycrt == ycross)
            {
                nsteps1 += abs(xcross-xcrt);
                break;
            }
            else
            {
                nsteps1 += abs(ynew-ycrt)+abs(xnew-xcrt);
            }
        }


        int nlines2 = vlines[1].size();
        int nsteps2 = 0;
        for (int jlines = 0 ; jlines < nlines2 ; ++jlines)
        {
            int xcrt = vlines[1][jlines].point1.x;
            int xnew = vlines[1][jlines].point2.x;
            int ycrt = vlines[1][jlines].point1.y;
            int ynew = vlines[1][jlines].point2.y;

            if (xcrt == xnew && xcrt == xcross)
            {
                nsteps2 += abs(ycross - ycrt);
                break;
            }
            else if (ycrt == ynew && ycrt == ycross)
            {
                nsteps2 += abs(xcross-xcrt);
                break;
            }
            else
            {
                nsteps2 += abs(ynew-ycrt)+abs(xnew-xcrt);
            }
        }

        if (nsteps1+nsteps2 < nstepsmin)
        {
            nstepsmin = nsteps1 + nsteps2;
        }
    }

    fout << "part 2: "<< nstepsmin;

    return 0;
}
