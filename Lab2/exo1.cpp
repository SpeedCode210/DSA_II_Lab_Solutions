#include <iostream>
#include <functional>
#include <chrono>
using namespace std;
using namespace chrono;
#define int long long

function<int(int)> f1 = [](int n)
{ // O(N)
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += 1;
    return sum;
};

function<int(int)> f2 = [](int n)
{ // O(N^2)
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sum += 1;
    return sum;
};

function<int(int)> f3 = [](int n)
{ // O(N^3)
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n*n; j++)
            sum += 1;
    return sum;
};

function<int(int)> f4 = [](int n)
{ // O(N^2)
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            sum += 1;
    return sum;
};

function<int(int)> f5 = [](int n)
{ // O(N^5)
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i*i; j++)
            for(int k = 0; k < j; k++)
                sum += 1;
    return sum;
};


function<int(int)> f6 = [](int n) 
{ // O(N^4)
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i * i; j++)
        {
            if (j % i == 0)
            {
                for (int k = 0; k < j; k++)
                {
                    sum += 1;
                }
            }
        }
    }

    return sum;
};

signed main()
{
    vector<int> values = {10,20,30,40,50,60};

    vector<function<int(int)>> functions = {f1,f2,f3,f4,f5,f6};

    for(int i = 0; i < functions.size(); i++){
        cout << "Function " << i+1 << " :\n";
        for (int j = 0; j < values.size(); j++){
            auto start = high_resolution_clock::now();
            int k = functions[i](values[j]);
            auto end = high_resolution_clock::now();
            cout << values[j] << " | " << (end-start).count() << '\n';
        } 
    }
}