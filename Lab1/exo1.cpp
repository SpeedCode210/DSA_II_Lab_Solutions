#include <iostream>
#include <vector>
#include <queue>
typedef long long ll;
using namespace std;

struct Node
{
    Node *children[26];
    int isEndOf = -1;

    Node()
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isEndOf = -1;
    }
};

int main()
{
    cout << "Enter the grid dimensions (#Lines # Columns):\n";
    int N, M, K;
    cin >> N >> M;
    cout << "Enter the grid :\n";
    vector<string> grid(N);
    for (int i = 0; i < N; i++)
        cin >> grid[i];

    cout << "Enter the number of words :\n";
    cin >> K;
    vector<string> words(K);
    vector<bool> found(K, false);
    cout << "Enter the words one by one :\n";
    for (int i = 0; i < K; i++)
        cin >> words[i];

    // inserting the words into a trie DS
    Node *trieRoot = new Node();
    for (int i = 0; i < K; i++)
    {
        Node *current = trieRoot;
        for (auto &c : words[i])
        {
            if (current->children[c - 'A'] == nullptr)
            {
                current->children[c - 'A'] = new Node();
            }
            current = current->children[c - 'A'];
        }
        current->isEndOf = i;
    }

    // Checking if each word appears
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (a == 0 and b == 0)
                        continue;
                    int x = i;
                    int y = j;
                    Node *current = trieRoot;
                    while (x < N and y < M and x >= 0 and y >= 0)
                    {
                        current = current->children[grid[x][y] - 'A'];
                        if (current == nullptr)
                            break;
                        if (current->isEndOf > -1)
                            found[current->isEndOf] = true;

                        x += a;
                        y += b;
                    }
                }
            }
        }

    cout << "Found Words :\n";
    for (int i = 0; i < K; i++)
    {
        if (found[i])
            cout << words[i] << '\n';
    }

    // Cleaning memory from trie nodes
    queue<Node*> to_clean;
    to_clean.push(trieRoot);
    while(to_clean.size()){
        Node* curr = to_clean.front();
        to_clean.pop();
        for(Node* child : curr->children){
            if(child != nullptr) to_clean.push(child);
        }
        delete curr;
    }
}