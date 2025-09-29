#include <iostream>
#include <vector>
using namespace std;

template <typename Comparable>
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

int main()
{
    int N, K;
    cout << "Enter the values of N and K separated by a space : ";
    cin >> N >> K;
    vector<int> A(N);
    cout << "Enter the values of the array :\n";
    for (int i = 0; i < N; i++)
        cin >> A[i];

    bubble_sort<int>(A);

    cout << "The K-th largest number is : " << A[K-1] << '\n';
}