#include <fstream>
#include <iostream>
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

void initialize(map < string, pair < long long, vector < pair < long long, string > > > > & mapp, map < string, long long > & inventory)
{
	bool eof = 0;
	while (!eof)
	{
		long long amount;
		string name;
		vector < pair < long long, string > > vReactants;
		while (1)
		{
			fin >> amount;
			if (amount < 0)
			{
				if (amount == -9)
				{
					eof = 1;
					break;
				}
				fin >> amount >> name;
				pair < long long, vector < pair < long long, string > >> details(amount, vReactants);

				if (mapp.find(name) != mapp.end())
				{
					fout << "that would mean the assumption that you can obtain an element in a singular way is wrong";
					exit(1);
				}
				mapp[name] = details;
				inventory[name] = 0;
				break;
			}
			fin >> name;
			pair < long long, string > pairElem(amount, name);
			vReactants.push_back(pairElem);

		}
	}
}

void fPart1(map < string, pair < long long, vector < pair < long long, string > > > > mapp, map < string, long long > inventory)
{
	long long sum = 0;
	demand(1, "FUEL", mapp, inventory, sum);
	fout << "part 1 : " << sum << "\n";
}

void fPart2(map < string, pair < long long, vector < pair < long long, string > > > > mapp, map < string, long long > inventory)
{
	const long long BIG = 10000000;
	const long long TRILLION = 1000000000000;
	long long lo = 1;
	long long hi = BIG;
	long long mid = 0,answer=0,from = 0;
	while (lo <= hi)
	{
		long long mid = (lo + hi) / 2;
		long long sum = 0;
		demand(mid, "FUEL", mapp, inventory, sum);
		inventory.clear();
		if (sum > TRILLION)
		{
			hi = mid - 1;
		}
		else
		{
			answer = mid;
			from = sum;
			lo = mid + 1;

		}
	}

	fout << "part 2 : " << answer << " FUEL produced from " << from << " ores \n";
	fout << "checking for off-by-one errors: " << "\n";

	inventory.clear();
	long long sum = 0;
	demand(answer-1, "FUEL", mapp, inventory, sum);
	fout << answer-1 << " FUEL produced from " << sum << " ores \n";
	
	inventory.clear();
	sum = 0;
	demand(answer , "FUEL", mapp, inventory, sum);
	fout << answer  << " FUEL produced from " << sum << " ores \n";
	
	inventory.clear();
	sum = 0;
	demand(answer+1 , "FUEL", mapp, inventory, sum);
	fout << answer+1  << " FUEL produced from " << sum << " ores \n";

}
int main()
{
	map < string, pair < long long, vector < pair < long long, string > > > > mapp;
	map < string, long long > inventory;
	initialize(mapp, inventory);

	fPart1(mapp,inventory);
	cout << "part 1 finished, wait some seconds for part 2...\n";
	fPart2(mapp,inventory);


	
	//fPart2(mapp, inventory);
	return 0;
}