#include <fstream>

using namespace std;

ifstream fin ("d04.in");
ofstream fout("d04.out");

//int lft,rgt,npass=0,idigit,digit,dif;
//char car;
//int pwr,olddigit;
//bool isincreasing,adjprop;

const int part2 = 1;

int main()
{

    int lft,rgt,npass=0;
    char car;
    fin >> lft >> car >> rgt;

    for (int inr=lft ; inr<=rgt ; ++inr)
    {
        int pwr = 100000;
        int olddigit=0;
        int isincreasing = 1;
        int  adjprop=0;

        for (int  idigit = 5 ; idigit>=0 ; --idigit)
        {
            int digit = inr / pwr % 10;

            if (digit < olddigit)
            {
                isincreasing = 0;
                break;
            }
            else
            {
                int olderdigit = inr/(pwr*100) % 10;
                int followingdigit = 0;
                if (pwr >= 10)
                {
                    followingdigit = inr/(pwr/10)%10;
                }

                if (digit == olddigit)
                {
                    if (!part2 || (digit!= olderdigit && digit!=followingdigit))
                    {
                        adjprop=1;
                    }
                }
            }
            pwr/=10;
            olddigit = digit;
        }

        if (isincreasing && adjprop)
        {
            ++npass;
            fout << "pass : " << inr << '\n';
        }
    }


    fout <<"part ";

    if (part2) fout << 2 << " : ";
    else fout << 1 << " : " ;

    fout << npass << '\n';

    return 0;
}
