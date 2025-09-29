#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

template <class Comparable>
void bubble_sort(vector<Comparable> &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 1; j < a.size() - i; j++)
        {
            if (a[j] > a[j - 1])
                swap(a[j], a[j - 1]);
        }
    }
}

int f(int N)
{
    auto start = chrono::high_resolution_clock::now();
    int K = max(N / 2, 1);
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        A[i] = rand() % 1000;
    bubble_sort<int>(A);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count();
}

int main()
{
    srand(time(0));

    for(auto n : {10, 50, 100, 500, 1000, 5000, 10000}){
        cout << n << " | " << f(n) << " microseconds.\n";
    }
}