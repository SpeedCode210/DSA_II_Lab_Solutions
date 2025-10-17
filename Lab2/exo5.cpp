#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int candidate(vector<int> &a)
{
    if (a.size() == 1)
        return a[0];
    vector<int> b;
    for (int i = 1; i < a.size(); i += 2)
        if (a[i] == a[i - 1])
            b.push_back(a[i]);

    if (b.size())
    {
        return candidate(b);
    }
    else
    {
        return a[a.size() - 1];
    }
}

signed main()
{
    vector<int> a = {1,8,2,8,3,8,8};
    int cand = candidate(a);
    int c = 0;
    for(int i = 0; i < a.size(); i++)
    if(a[i] == cand) c++;

    cout << (c >= (a.size()+2)/2 ? "YES" : "NO") << endl;
}