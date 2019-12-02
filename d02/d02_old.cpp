#include <fstream>
#include <cstring>

using namespace std;


//ifstream parse("d02_parse.in");
//ofstream parseout("d02.in");
ifstream fin ("d02.in");
ofstream fout("d02.out");

int main()
{
    int vpoz[10000],vpozbak[10000],npoz=0;
//    char vparse[1000];
//    parse >> vparse;
//    int lgparse = strlen(vparse);
//    for (int i=0;i<lgparse;++i)
//    {
//        if (vparse[i]==',')
//        {
//            vparse[i]=' ';
//        }
//    }
//    parseout << vparse;
//

    while (fin >> vpoz[npoz])
    {
        ++npoz;
    }

    for (int jpoz=0; jpoz<npoz; ++jpoz)
    {
        vpozbak[jpoz] = vpoz[jpoz];
    }


    int ipoz=0;

    ///int noun = vpoz[1],verb = vpoz[2];

    for (int noun = 0 ; noun < 100 ; ++noun)
    {
        for (int verb = 0 ; verb < 100; ++verb)
        {


            //for (int jpoz=0; jpoz<npoz; ++jpoz) vpoz[jpoz] = vpozbak[jpoz];

            for (int jpoz=0; jpoz<npoz;++jpoz) vpoz[jpoz]=vpozbak[jpoz];

            vpoz[1]=noun; //=12;
            vpoz[2]=verb; //=2;

            //for (int jpoz=0; jpoz<npoz; ++jpoz) fout << vpoz[jpoz] << ' '; fout << '\n';
            int ipoz=0;
            while (ipoz<npoz)
            {
                if (vpoz[ipoz] == 99)
                {
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

            if (vpoz[0] == 19690720)
            {
                fout << "100 * noun + verb is " << 100 * noun + verb <<'\n';
                return 0;
            }
        }
    }



    return 0;

}






