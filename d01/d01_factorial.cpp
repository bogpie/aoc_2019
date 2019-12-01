#include <fstream>

using namespace std;

ifstream fin ("d01.in");
ofstream fout("d01.out");

int part1 (int mass,int &fuelReq)
{
    fuelReq = mass / 3 - 2;
}

int part2 (int mass)
{
    if (mass<=0) return 0;
    if (mass<6) mass = 6;
    return mass/3-2 + part2(mass/3-2);
}

int main ()
{
    unsigned long long sum = 0;

    int mass;
    while (fin >> mass)
    {
        int fuelReq = 0 ;
        ///part1 (mass,fuelReq);
        fuelReq =  part2(mass);
        sum += fuelReq;
    }

    fout << sum;
}
