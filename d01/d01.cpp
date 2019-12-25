#include <fstream>

using namespace std;

ifstream fin ("d01.in");
ofstream fout("d01.out");

void part1 (int mass,int &fuelReq)
{
    fuelReq = mass / 3 - 2;
}

void part2 (int mass,int &fuelReq)
{
    while (mass>0)
    {
        mass = mass / 3 - 2;
        if (mass < 0) mass = 0;
        fuelReq += mass;
    }
}

int main ()
{
    unsigned long long sum = 0;

    int mass;
    while (fin >> mass)
    {
        int fuelReq = 0 ;
        //part1 (mass,fuelReq); // for part 1 run this & don't run below function
        part2 (mass,fuelReq);
        sum += fuelReq;
    }

    fout << sum;
}
