#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <algorithm>

#define GET_RAND rand() % 95 + 32   // 32 - 126

using namespace std;

struct progeny
{
    progeny(){}
    progeny(string word_string) : s(word_string) {}
    string s;
    int fitness = 0;
};

void Mutate(vector<progeny> &v, int mutation);
int CorrectOrder(string a, string b);
int CorrectLetters(string a, string b);
void EvaluateFitness(progeny &p, string b);
bool FitnessSort(const progeny &lhs, const progeny &rhs){return lhs.fitness > rhs.fitness;};

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Too few arguments! Enter a phrase starting argument:\nphrase_finder_GA To boldly go.\n";
        return 1;
    }

    srand(time(NULL));

    string words;
    for (int i = 1; i < argc; ++i)
        words += string(argv[i]) + " ";
    
    words.pop_back();

    unsigned int phr_size = words.size();

    int pool_size, mutation, saved_population;
    cout << "Enter desired pool size(ex: 100): ";
    cin >> pool_size;

    cout << "\nEnter desired mutation rate in integer percentages(ex: 5): ";
    cin >> mutation;

    cout << "\nEnter desired percentage of population to keep each generation(ex: 5): ";
    cin >> saved_population;

    // Build initial pool
    vector<progeny> pool(pool_size);
    for (int i = 0; i < pool_size; ++i)
    {
        string random_str;
        for (unsigned int j = 0; j < words.size(); ++j)
            random_str += GET_RAND;
        pool[i].s = random_str;
    }

    vector<progeny> new_generation;
    int cutoff = max(1.0,pool_size * saved_population / 100.0);
    int match = words.size()*words.size() + CorrectLetters(words,words);
    unsigned int generations = 0;
    while (true)
    {
        ++generations;
         // Evaluate
        for (int i = 0; i < pool_size; ++i)
            EvaluateFitness(pool[i], words);

        // Order by fitness
        sort(pool.begin(), pool.end(), FitnessSort);
        cout << "best: " << pool[0].s << "\nfitness: " << 100.0 * pool[0].fitness / match  << "%\tgeneration: " << generations << endl << endl;
        if (pool[0].fitness == match)
            return 0;

        for (int i = 0; i < cutoff; ++i)
            new_generation.emplace_back(pool[i]);

        pool.clear();
        // Breed
        for (int i = 0; i < pool_size; ++i)
        {
            string first_progenitor = new_generation[rand() % cutoff].s;

            // Wanted to make this not equal to the first parent but can't because infinite loops with small pools/saved_population sizes
            string second_progenitor = new_generation[rand() % cutoff].s;
            pool.emplace_back(progeny(first_progenitor.substr(0,phr_size/2) + second_progenitor.substr(phr_size/2)));
        }

        // Mutate
        Mutate(pool,mutation);

        new_generation.clear();
    }

    return 0;
}

// Each character has "mutation" chance to be mutated
void Mutate(vector<progeny> &v, int mutation)
{
    for (unsigned int i = 0; i < v.size(); ++i)
        for (unsigned int j = 0; j < v[i].s.size(); ++j)
            if (rand() % 101 <= mutation)
                v[i].s[j] = GET_RAND; // small chance the mutation is the same value, deciding to ignore      
}

// Helper for the fitness evaluation. Finds count of letters in the correct order.
int CorrectOrder(string a, string b)
{
    int ret_val = 0;
    for (unsigned int i = 0; i < a.size(); ++i)
        if (a[i] == b[i])
            ++ret_val;

    return ret_val;
}

// Helper for fitness evaluation. Finds number of correct letters, counts repeats.
int CorrectLetters(string a, string b)
{
    int ret_val = 0;
    for (unsigned int i = 0; i < a.size(); ++i)
        for(unsigned int j = 0; j < b.size(); ++j)
            if (a[i] == b[j])
                ++ret_val;

    return ret_val;
}

// Evaluates the fitness of a progeny
void EvaluateFitness(progeny &p, string b)
{
    p.fitness = CorrectOrder(p.s, b);
    p.fitness *= p.fitness;
    p.fitness += CorrectLetters(p.s, b);
}