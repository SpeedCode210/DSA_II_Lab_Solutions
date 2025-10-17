#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> generate_random_1(int size)
{
    vector<int> a(size);
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % size + 1;
        for (int j = 0; j < i; j++)
            if (a[j] == a[i])
            {
                i--;
                continue;
            }
    }

    return a;
}

vector<int> generate_random_2(int size)
{
    vector<int> a(size);
    vector<bool> used(size, false);
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % size + 1;
        if (used[a[i] - 1])
        {
            i--;
            continue;
        }
        used[a[i] - 1] = true;
    }

    return a;
}

vector<int> generate_random_3(int size)
{
    vector<int> a(size);
    for (int i = 0; i < size; i++)
    {
        a[i] = i + 1;
    }

    for (int i = 1; i < size; i++)
        swap(a[i], a[rand() % i]);

    return a;
}

signed main()
{
    srand(0);

    vector<function<vector<int>(int)>> algos = {generate_random_1, generate_random_2, generate_random_3};
    ll NB_TRIES = 20;
    vector<int> N = {250, 500, 1000, 2000};

    for (auto n : N)
    {
        for (int j = 0; j < 3; j++)
        {
            auto algo = algos[j];
            auto begin = chrono::high_resolution_clock::now();
            for (int i = 0; i < NB_TRIES; i++)
            {
                algo(n);
            }
            auto end = chrono::high_resolution_clock::now();

            cout << "ALGO" << j << " : " << n << " | " << (end-begin).count()/1000000LL/NB_TRIES << "ms\n";
        }
    }
}