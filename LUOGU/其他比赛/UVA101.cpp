#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const int MAXN = 25;
vector<int> piles[MAXN];
int pos[MAXN];

int findpile(int a) {
    return pos[a];
}

void init(int n) {
    for (int i = 0; i < n; i++) {
        piles[i].clear();
        piles[i].push_back(i);
        pos[i] = i;
    }
}

void clear_above(int a) {
    int p = pos[a];
    int idx = 0;
    while (piles[p][idx] != a) idx++;
    for (int i = idx + 1; i < (int)piles[p].size(); i++) {
        int block = piles[p][i];
        piles[block].push_back(block);
        pos[block] = block;
    }
    piles[p].resize(idx + 1);
}

void move_block(int a, int dest) {
    int p = pos[a];
    piles[p].pop_back();
    piles[dest].push_back(a);
    pos[a] = dest;
}

void stack_move(int a, int dest) {
    int p = pos[a];
    int idx = 0;
    while (piles[p][idx] != a) idx++;
    for (int i = idx; i < (int)piles[p].size(); i++) {
        int block = piles[p][i];
        piles[dest].push_back(block);
        pos[block] = dest;
    }
    piles[p].resize(idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string line;
    
    while (cin >> n) {
        cin.ignore();
        init(n);
        
        while (getline(cin, line)) {
            if (line == "quit") break;
            
            istringstream iss(line);
            string cmd1, cmd2;
            int a, b;
            iss >> cmd1 >> a >> cmd2 >> b;
            
            if (a == b) continue;
            if (pos[a] == pos[b]) continue;
            
            if (cmd1 == "move") {
                clear_above(a);
                if (cmd2 == "onto") {
                    clear_above(b);
                }
                move_block(a, pos[b]);
            } else {
                if (cmd2 == "onto") {
                    clear_above(b);
                }
                stack_move(a, pos[b]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << i << ":";
            for (int j = 0; j < (int)piles[i].size(); j++) {
                cout << " " << piles[i][j];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
