#include <fstream>
#include <cstring>

using namespace std;

ifstream fin ("d02.in");
ofstream fout("d02.out");

const int GIVEN_CONSTANT = 19690720;

int main()
{
    char comma;
    int vpoz[10000],vpozbak[10000],npoz=0;

    while (fin >> vpoz[npoz] >> comma)
    {
        ++npoz;
    }

    for (int jpoz=0; jpoz<npoz; ++jpoz)
    {
        vpozbak[jpoz] = vpoz[jpoz];
    }


    int ipoz=0,part1_sol;

    ///int noun = vpoz[1],verb = vpoz[2];


    for (int noun = 0 ; noun < 100 ; ++noun)
    {
        for (int verb = 0 ; verb < 100; ++verb)
        {

            for (int jpoz=0; jpoz<npoz;++jpoz) vpoz[jpoz]=vpozbak[jpoz];

            vpoz[1]=noun; //=12;
            vpoz[2]=verb; //=2;

            int ipoz=0;
            while (ipoz<npoz)
            {
                if (vpoz[ipoz] == 99)
                {
                    if (noun == 12 && verb == 2)
                    {
                        fout << "useful for part 1\n";
                        part1_sol = vpoz[0];
                    }
                    fout << "position 0 : " << vpoz[0] << " for noun and verb pair : " << noun << " and " << verb << '\n';
                    //return 0;
                    break;
                }
                else if (vpoz[ipoz] == 1)
                {
                    vpoz[vpoz[ipoz+3]] = vpoz[vpoz[ipoz+1]] + vpoz[vpoz[ipoz+2]];
                }
                else if (vpoz[ipoz]==2)
                {
                    vpoz[vpoz[ipoz+3]] = vpoz[vpoz[ipoz+1]] * vpoz[vpoz[ipoz+2]];
                }
                else
                {
                    fout << " something else ";
                    return 0;
                }
                ipoz+=4;

                //for (int jpoz=0;jpoz<npoz;++jpoz) fout << vpoz[jpoz] << ' ';
                //fout << '\n';
            }

            if (vpoz[0] == GIVEN_CONSTANT)
            {
                fout << "!!! part 1 solution is " << part1_sol << "\n";


                fout << "found GIVEN_CONSTANT in vpoz[0] when noun is " << noun << " and verb is " << verb << '\n';
                fout << "!!! part 2 solution is 100 * noun + verb , that means " << 100 * noun + verb <<'\n';
                return 0;
            }
        }
    }



    return 0;

}






