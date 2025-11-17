#include "PasswordCracker.h"

using namespace std;

void PasswordCracker()
{
	vector<string> hashList;
	ifstream hashInput("passwords_notfound.txt");
	string line;

	while (getline(hashInput, line))
	{
		hashList.push_back(line);
	}

	for (long long i = 0; i < 9999999999; i++)
	{
		for (int j = 0; j < hashList.size(); j++)
		{
			
		}
	}
}