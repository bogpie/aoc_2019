#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ifstream fin("d14_parsed.txt");
ofstream fout("d14_out.txt");

void demand(long long amount, string name, map < string, pair < long long, vector < pair < long long, string > > > > mapp, map < string, long long > & inventory,long long & sum)
{
	if (!name.compare("ORE"))
	{
		sum+= amount;
		return;
	}

	auto resulted = mapp[name].first;
	auto vReactants = mapp[name].second;
	amount -= inventory[name];
	inventory[name] = 0;
	if (amount <=0)
	{
		inventory[name] += (-amount);
		amount = 0;
		return;
	}

	long long nRepeats = amount / resulted;
	if (amount % resulted)
	{
		++nRepeats;
		inventory[name] += resulted * nRepeats - amount;
	}

	for (long long i = 0; i < vReactants.size(); ++i)
	{
		auto reactant = vReactants[i];
		demand(nRepeats * reactant.first, reactant.second, mapp, inventory, sum);
	}

}

int main()
{
	string line;
	map < string, pair < long long, vector < pair < long long, string > > > > mapp;
	map < string, long long > inventory;

	bool eof = 0;
	while (!eof)
	{
		long long amount;
		string name;
		vector < pair < long long, string > > vReactants;
		while (1)
		{
			fin >> amount;
			if (amount<0)
			{
				if (amount == -9)
				{
					eof = 1;
					break;
				}
				fin >> amount >> name;
				pair < long long, vector < pair < long long, string > >> details(amount, vReactants);
				
				if (mapp.find(name)!=mapp.end())
				{
					fout << "that would mean the assumption that you can obtain an element in a singular way is wrong";
					exit(1);
				}
				mapp[name] = details;
				inventory[name] = 0;
				break;
			}
			fin >> name;
			pair < long long, string > pairElem(amount,name);
			vReactants.push_back(pairElem);
		
		} 
	}

	long long sum = 0;
	demand(1,"FUEL",mapp,inventory,sum);
	fout << "part 1 : " << sum << "\n";
	return 0;
}