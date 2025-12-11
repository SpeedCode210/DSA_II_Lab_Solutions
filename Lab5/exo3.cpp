#include <bits/stdc++.h>
using namespace std;

/*
1. The data structure used for implementation is vector
2. To insert : we call the findPos function which finds the target cell of the array where the element will be stored, using quadratic probing, then if the object is already in there it isnt inserted, else we do, and rehash if there are more than N/2 elements in the hashtable.
*  To delete : we call the findPos function which finds the target cell of the array where the element should be stored, and if found we mark the cell as deleted.
3. Collision handling is dealth with in the findPos function, which uses quadratic probing.
4. Rehashing is done when half the capacity of the table is reached, because when it is, when a collision happens we might try all possible cells and won't find a good one, this is because for P prime there are (P-1)/2 quadratic residues.
*/

signed main() {
   
}