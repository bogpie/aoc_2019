#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ifstream parsedIn("d14_in.txt");
ofstream parsedOut("d14_parsed.txt");

int main()
{
	string line;
	while (getline(parsedIn, line))
	{
		while (1)
		{
			int found = line.find(",");
			if (found == -1) break;
			line[found] = ' ';
		}
		int found = line.find("=");
		line[found] = '-';
		line[found + 1] = '1';
		parsedOut << line << "\n";
	}
	parsedOut << -9;

	return 0;
}