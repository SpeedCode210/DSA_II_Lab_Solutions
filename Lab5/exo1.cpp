#include <iostream>
using namespace std;

const int TABLE_SIZE = 1000;

int hashtable[TABLE_SIZE];

void insert(int val)
{
    hashtable[val % TABLE_SIZE] += 1;
}

void remove(int val)
{
    if (hashtable[val % TABLE_SIZE])
        hashtable[val % TABLE_SIZE] -= 1;
}

bool search(int val)
{
    return hashtable[val % TABLE_SIZE] > 0;
}

signed main()
{
    srand(time(0));

    for (int i = 0; i < TABLE_SIZE; i++)
        hashtable[i] = 0;

    for(int i = 0; i < TABLE_SIZE*2/10; i++){
        insert(rand());
    }

    int nbCol = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        nbCol += hashtable[i]*(hashtable[i]-1)/2;
    }
    cout << "For 20% of the table capacity, there are : " << nbCol << " collisions." << '\n';

    for(int i = 0; i < TABLE_SIZE*3/10; i++){
        insert(rand());
    }

    nbCol = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        nbCol += hashtable[i]*(hashtable[i]-1)/2;
    }
    cout << "For 50% of the table capacity, there are : " << nbCol << " collisions." << '\n';

    for(int i = 0; i < TABLE_SIZE*3/10; i++){
        insert(rand());
    }

    nbCol = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        nbCol += hashtable[i]*(hashtable[i]-1)/2;
    }
    cout << "For 80% of the table capacity, there are : " << nbCol << " collisions." << '\n';
}