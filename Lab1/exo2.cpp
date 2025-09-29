#include <iostream>
#include <vector>
using namespace std;

void showPermutations(string &s, vector<bool>& flags, string prefix = ""){
    if(prefix.size() == s.size()){
        cout << prefix << '\n';
        return;
    }

    for (int i = 0; i < s.size(); i++) {
        if(flags[i])continue;
        flags[i] = true;
        showPermutations(s, flags, prefix + s[i]);
        flags[i] = false;
    }
}

int main(){
    string S;
    cout << "Enter your string :" << endl;
    cin >> S;
    vector<bool> flags(S.size(), false);
    showPermutations(S, flags);

}