#include <iostream>
using namespace std;

bool isPrime(long long n){
    for(long long i = 2; i*i <= n; i++)
        if(n%i == 0) return false;
    return true;
}

int main(){
    cout << "Enter an integer N : ";
    long long N;
    cin >> N;
    cout << (isPrime(N) ? "It is a prime" : "It is composite") << endl;
}