#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#define GET_RAND rand() % 95 + 32   // 32 - 126

using namespace std;

struct progeny
{
    string s;
    int fitness = 0;
};

void Mutate(vector<progeny> &v, int mutation);
int CorrectOrder(string a, string b);

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

    unsigned int phr_size = words.size();

    int pool_size, mutation;
    cout << "Enter desired pool size: ";
    cin >> pool_size;

    cout << "\nEnter desired mutation rate in integer percentages(ex: 5): ";
    cin >> mutation;

    // Build initial pool
    vector<string> pool(pool_size);
    for (int i = 0; i < pool_size; ++i)
    {
        string random_str;
        for (unsigned int j = 0; j < words.size(); ++j)
            random_str += GET_RAND;
        pool[i] = random_str;
    }


    // while (true)
    {
        vector<progeny> new_generation(pool_size);
        // Breed
        for (int i = 0; i < pool_size; ++i)
        {
            string first_progenitor = pool[rand() % pool_size];
            string second_progenitor;
            do 
            {
                second_progenitor = pool[rand() % pool_size];
            }while (first_progenitor == second_progenitor);
            new_generation[i].s = first_progenitor.substr(0,phr_size/2) + second_progenitor.substr(phr_size/2);
        }
        // Mutate
        Mutate(new_generation,mutation);

        // Evaluate
        for (int i = 0; i < pool_size; ++i)
        {
            int worth = CorrectOrder(new_generation[i].s,words);
            new_generation[i].fitness = worth * worth;
        }
    }

    return 0;
}

void Mutate(vector<progeny> &v, int mutation)
{
    for (unsigned int i = 0; i < v.size(); ++i)
        for (unsigned int j = 0; j < v[i].s.size(); ++j)
            if (rand() % 101 <= mutation)
                v[i].s[j] = GET_RAND; // small chance the mutation is the same value, deciding to ignore      
}

int CorrectOrder(string a, string b)
{
    int ret_val = 0;
    for (unsigned int i = 0; i < a.size(); ++i)
        if (a[i] == b[i])
            ++ret_val;
    return ret_val;
}

