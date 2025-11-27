#include "PasswordCracker.h"

using namespace std;

string GetHexRepresentation(const unsigned char* Bytes, size_t Length) {
	string ret(Length * 2, '\0');
	const char* digits = "0123456789abcdef";
	for (size_t i = 0; i < Length; ++i) {
		ret[i * 2] = digits[(Bytes[i] >> 4) & 0xf];
		ret[i * 2 + 1] = digits[Bytes[i] & 0xf];
	}
	return ret;
}

int PasswordCracker()
{
	vector<string> hashList;
	vector<string> dictionary;
	string passwordsToFindFile = "passwords_notfound.txt";
	string temporaryFileName = "TemporaryFile.txt";
	string foundFileName = "passwords_found.txt";
	string dictionaryFileName = "dictionary.txt";
	ifstream dictionaryFile(dictionaryFileName);
	ifstream hashInput(passwordsToFindFile);
	ofstream tempFile(temporaryFileName);
	ofstream foundFile(foundFileName, ios_base::app);
	string fileReadBuffer;
	string hashOutputInStringForm;
	string stringBuffer;
	string firstWord;
	unsigned char outBuf[20];


	if (!hashInput.is_open() || !tempFile.is_open())
	{
		cerr << "Error opening files" << endl;
		return 1;
	}

	while (getline(hashInput, fileReadBuffer))
	{
		hashList.push_back(fileReadBuffer);
	}

	hashInput.close();

	//hashList.push_back("356a192b7913b04c54574d18c28d46e6395428ab"); //sha1 hash value computed from plaintext value: 1, used for testing


	//SHA1(plaintext, strlen((char*)plaintext), outBuf);
	//hashOutputInStringForm = GetHexRepresentation(outBuf, sizeof(outBuf));

	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	//Iterating through all purely numerical values
	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	/*
	stringBuffer = "0";
	for (int i = 0; i < 9; i++)
	{
		SHA1(reinterpret_cast<const unsigned char*>(stringBuffer.data()), stringBuffer.length(), outBuf);
		hashOutputInStringForm = GetHexRepresentation(outBuf, sizeof(outBuf));

		for (int j = 0; j < hashList.size(); j++)
		{
			if (hashOutputInStringForm == hashList[j])
			{
				cout << "Hash found: " << hashList[j] << endl;

				for (int k = 0; k < hashList.size(); k++)
				{
					if (hashList[k] != hashList[j])
					{
						tempFile << hashList[k] << endl;

					}
				}
				tempFile.close();

				if (!foundFile.is_open())
				{
					cerr << "Error opening found file" << endl;
					return 1;
				}
				foundFile << "Password '" << stringBuffer << "' evaluates to hash: " << hashOutputInStringForm << endl;

				if (remove(originalFileName.c_str()) != 0)
				{
					cerr << "Error deleting original file" << endl;
					return 1;
				}

				if (rename(temporaryFileName.c_str(), originalFileName.c_str()) != 0)
				{
					cerr << "Error renaming temporary file." << endl;
					return 1;
				}

				hashInput.open(originalFileName);
				if (!hashInput.is_open())
				{
					cerr << "Error opening passwords_notfound file" << endl;
					return 1;
				}
				hashList.clear();

				while (getline(hashInput, fileReadBuffer))
				{
					hashList.push_back(fileReadBuffer);
				}

				hashInput.close();
			}
		}

		stringBuffer.push_back('0');
	}

	for (long long i = 0; i < 9999999999; i++)
	{
		stringBuffer = to_string(i);
		SHA1(reinterpret_cast<const unsigned char*>(stringBuffer.data()), stringBuffer.size(), outBuf);
		hashOutputInStringForm = GetHexRepresentation(outBuf, sizeof(outBuf));

		for (int j = 0; j < hashList.size(); j++)
		{
			if (hashOutputInStringForm == hashList[j])
			{
				cout << "Hash found: " << hashList[j] << endl;

				for (int k = 0; k < hashList.size(); k++)
				{
					if (hashList[k] != hashList[j])
					{
						tempFile << hashList[k] << endl;

					}
				}
				tempFile.close();

				if (!foundFile.is_open())
				{
					cerr << "Error opening file" << endl;
					return 1;
				}				
				foundFile << "Password '" << i << "' evaluates to hash: " << hashOutputInStringForm << endl;
				
				if (remove(originalFileName.c_str()) != 0) 
				{
					cerr << "Error deleting original file" << endl;
					return 1;
				}

				if (rename(temporaryFileName.c_str(), originalFileName.c_str()) != 0) 
				{
					cerr << "Error renaming temporary file." << endl;
					return 1;
				}

				hashInput.open(originalFileName);
				if (!hashInput.is_open())
				{
					cerr << "Error opening passwords_notfound file" << endl;
					return 1;
				}

				hashList.clear();

				while (getline(hashInput, fileReadBuffer))
				{
					hashList.push_back(fileReadBuffer);
				}

				hashInput.close();
			}
		}
	}
	*/

	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	//Testing -1- 2 word passwords
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	
	/*
	while (getline(dictionaryFile, fileReadBuffer))
	{
		dictionary.push_back(fileReadBuffer);
	}

	dictionaryFile.close();

	for (int i = 0; i < dictionary.size(); i++)
	{
		firstWord = dictionary[i];
		for (int j = 0; j < dictionary.size(); j++)
		{
			stringBuffer = firstWord;
			stringBuffer.string::append(dictionary[j]);
			
			SHA1(reinterpret_cast<const unsigned char*>(stringBuffer.data()), stringBuffer.size(), outBuf);
			hashOutputInStringForm = GetHexRepresentation(outBuf, sizeof(outBuf));

			for (int k = 0; k < hashList.size(); k++)
			{
				if (hashOutputInStringForm == hashList[k])
				{
					cout << "Hash found: " << dictionary[i] << dictionary[j] << " Evaluates to: " << hashList[k] << endl;

					for (int l = 0; l < hashList.size(); l++)
					{
						if (hashList[l] != hashList[k])
						{
							tempFile << hashList[l] << endl;

						}
					}
					tempFile.close();

					if (!foundFile.is_open())
					{
						cerr << "Error opening file" << endl;
						return 1;
					}
					foundFile << "Password '" << dictionary[i] << dictionary[j] << "' evaluates to hash: " << hashOutputInStringForm << endl;

					if (remove(passwordsToFindFile.c_str()) != 0)
					{
						cerr << "Error deleting original file" << endl;
						return 1;
					}

					tempFile.close();
					hashInput.close();
					if (rename(temporaryFileName.c_str(), passwordsToFindFile.c_str()) != 0)
					{
						cerr << "Error renaming temporary file." << endl;
						return 1;
					}

					hashInput.open(passwordsToFindFile);
					if (!hashInput.is_open())
					{
						cerr << "Error opening passwords_notfound file" << endl;
						return 1;
					}

					hashList.clear();

					while (getline(hashInput, fileReadBuffer))
					{
						hashList.push_back(fileReadBuffer);
					}

					hashInput.close();
				}
			}
		}
	}
	
	*/

	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	//Testing 1 word passwords with numbers appended
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	while (getline(dictionaryFile, fileReadBuffer))
	{
		dictionary.push_back(fileReadBuffer);
	}

	dictionaryFile.close();

	for (int i = 0; i < dictionary.size(); i++)
	{
		firstWord = dictionary[i];
		for (int j = 0; j < 999999; j++)
		{
			stringBuffer = firstWord;
			stringBuffer.string::append(to_string(j));

			SHA1(reinterpret_cast<const unsigned char*>(stringBuffer.data()), stringBuffer.size(), outBuf);
			hashOutputInStringForm = GetHexRepresentation(outBuf, sizeof(outBuf));

			for (int k = 0; k < hashList.size(); k++)
			{
				if (hashOutputInStringForm == hashList[k])
				{
					cout << "Hash found: " << stringBuffer << " Evaluates to: " << hashList[k] << endl;

					for (int l = 0; l < hashList.size(); l++)
					{
						if (hashList[l] != hashList[k])
						{
							tempFile << hashList[l] << endl;

						}
					}
					tempFile.close();

					if (!foundFile.is_open())
					{
						cerr << "Error opening file" << endl;
						return 1;
					}
					foundFile << "Password '" << stringBuffer << "' evaluates to hash: " << hashOutputInStringForm << endl;

					if (remove(passwordsToFindFile.c_str()) != 0)
					{
						cerr << "Error deleting original file" << endl;
						return 1;
					}

					tempFile.close();
					hashInput.close();
					if (rename(temporaryFileName.c_str(), passwordsToFindFile.c_str()) != 0)
					{
						cerr << "Error renaming temporary file." << endl;
						return 1;
					}

					hashInput.open(passwordsToFindFile);
					if (!hashInput.is_open())
					{
						cerr << "Error opening passwords_notfound file" << endl;
						return 1;
					}

					hashList.clear();

					while (getline(hashInput, fileReadBuffer))
					{
						hashList.push_back(fileReadBuffer);
					}

					hashInput.close();
				}
			}
		}
	}

	cout << "End of Password Cracker function" << endl;
	return 0;
}