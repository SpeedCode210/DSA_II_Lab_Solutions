#include "Vector.h"
#include <iostream>
using namespace std;

// Note : the testing code here was made using an LLM, but not the implementation dw :)

int main()
{
  Vector<int> v;

  cout << "Pushing 1, 2, 3...\n";
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  cout << "Initial vector: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "Inserting 99 at position 1...\n";
  v.insert(v.begin() + 1, 99);

  cout << "After insert: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "Erasing element at position 2...\n";
  v.erase(v.begin() + 2);

  cout << "After erase: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "Testing push_back & pop_back:\n";
  v.push_back(10);
  v.push_back(20);
  v.pop_back();

  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "Back element: " << v.back() << "\n";
}
