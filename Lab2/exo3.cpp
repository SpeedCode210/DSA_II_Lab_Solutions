#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int x = 0; int y = n-1;
    while(x <= y){
        int m = (x+y)/2;
        if(a[m] > m+1) y = m-1;
        else if(a[m] == m+1){
            cout << "YES\n";
            return 0;
        }else{
            x = m+1;
        }
    }
    cout << "NO\n";
}