#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#define GET_RAND rand() % 95 + 32	// 32 - 126

using namespace std;

void Mutate(vector<string> &v, int mutation);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Too few arguments! Enter a phrase starting argument:\nphrase_finder_GA To boldly go.\n";
		return 1;
	}

	srand(time(NULL));

	string words = "";
	for (int i = 1; i < argc; ++i)
		words += string(argv[i]) + " ";
	
	words.pop_back();

	int pool_size, mutation;
	cout << "Enter desired pool size: ";
	cin >> pool_size;

	cout << "\nEnter desired mutation rate in integer percentages(ex: 5): ";
	cin >> mutation;

	vector<string> pool(pool_size);
	for (int i = 0; i < pool_size; ++i)
	{
		string random_str;
		for (unsigned int j = 0; j < words.size(); ++j)
			random_str += GET_RAND;
		pool[i] = random_str;	
	}

	std::vector<string> v = pool;
	Mutate(pool, mutation);

	for (unsigned int i = 0; i < v.size(); ++i)
		cout << v[i] << endl << pool[i] << endl << endl;


	return 0;
}

void Mutate(vector<string> &v, int mutation)
{
	for (unsigned int i = 0; i < v.size(); ++i)
		for (unsigned int j = 0; j < v[i].size(); ++j)
			if (rand() % 101 <= mutation)
				v[i][j] = GET_RAND;	// small chance the mutation is the same value, deciding to ignore		
}