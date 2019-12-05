#include <fstream>

using namespace std;

ifstream fin ("d05.in");
ofstream fout ("d05.out");

int fOperation (int a,int b,int opcode)
{
    if (opcode == 1) return a + b;
    else if (opcode ==2) return a*b;
    //else
}

int replaceParameter (int param,int paramMode,int vProg[])
{
    if (paramMode == 0)
    {
        return vProg[param];
    }
    else if (paramMode == 1)
    {
        return param;
    }
//    else
//    {
//        exit(1);
//    }
}

int main()
{
    int vProg[1000],vParamMode[5],vNewParam[5];
    int nProg=0;
    char comma;

    while (!fin.eof())
    {
        fin >> vProg[nProg++] >> comma;
        if (comma == '\0')
        {
            break;
        }
    }

    int inpt = 5,iProg=0;

    while (1)
    {
        int old_iProg = iProg;

        int opcode = vProg[iProg]%10;
        vParamMode[1]=vProg[iProg]/100%10;
        vParamMode[2]=vProg[iProg]/1000%10;
        vParamMode[3]=vProg[iProg]/10000%10;


        if (opcode == 3)
        {
            vProg[vProg[iProg+1]]=inpt;
            iProg+=2;
        }
        else if (opcode == 4 )
        {
            fout << "Output : " << vProg[vProg[iProg+1]] << '\n';
            iProg+=2;
        }
        else  if (opcode == 9)
        {
            fout << "Opcode : " << opcode << '\n';
            fout << "vProg[iProg] : " << vProg[iProg] << '\n';
            fout << "HALT\n";
            break;
        }
        else
        {
             vNewParam[1] = replaceParameter(vProg[iProg+1],vParamMode[1],vProg);
             vNewParam[2] = replaceParameter(vProg[iProg+2],vParamMode[2],vProg);


            if (opcode == 1 || opcode ==2)
            {
                //vNewParam[3] = replaceParameter(vProg[iProg+3],vParamMode[3],vProg);

                vProg[vProg[iProg+3]] = fOperation(vNewParam[1],vNewParam[2],opcode);
                iProg+=4;
            }
            else if ( (opcode == 5 && vNewParam[1]) || (opcode == 6 && !vNewParam[1] ) )
            {
                iProg = vNewParam[2];
            }
            else if (opcode == 7)
            {
                if (vNewParam[1] < vNewParam[2])
                {
                     vProg[vProg[iProg+3]] = 1;
                }
                else vProg[vProg[iProg+3]] = 0;
                iProg+=4;
            }
            else if (opcode == 8)
            {
                if (vNewParam[1] == vNewParam[2])
                {
                     vProg[vProg[iProg+3]] = 1;
                }
                else vProg[vProg[iProg+3]] = 0;
                iProg+=4;

            }
        }

        if (iProg == old_iProg)
        {
            iProg += 3;
        }

    }

    return 0;
}
