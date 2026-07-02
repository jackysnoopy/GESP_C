#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int n;
vector<char> vars;
bool adj[26][26];
bool used[26];
char order[26];

void dfs(int depth, vector<int>& inDeg) {
    if (depth == n) {
        for (int i = 0; i < n; i++) cout << order[i] << (i < n - 1 ? " " : "\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        int idx = vars[i] - 'a';
        if (!used[idx] && inDeg[idx] == 0) {
            used[idx] = true;
            order[depth] = vars[i];
            vector<int> newDeg(inDeg);
            for (int j = 0; j < 26; j++) {
                if (adj[idx][j]) newDeg[j]--;
            }
            dfs(depth + 1, newDeg);
            used[idx] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    bool first = true;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "#") break;

        vars.clear();
        memset(adj, 0, sizeof(adj));
        memset(used, 0, sizeof(used));

        for (char c : line) {
            if (c != ' ') vars.push_back(c);
        }
        sort(vars.begin(), vars.end());
        n = vars.size();

        vector<int> inDeg(26, 0);
        string constraintLine;
        while (getline(cin, constraintLine)) {
            if (constraintLine == "#" || constraintLine.empty()) {
                if (constraintLine == "#") break;
                continue;
            }
            char x = constraintLine[0], y = constraintLine[2];
            if (!adj[x - 'a'][y - 'a']) {
                adj[x - 'a'][y - 'a'] = true;
                inDeg[y - 'a']++;
            }
        }

        if (!first) cout << "\n";
        first = false;
        dfs(0, inDeg);
    }

    return 0;
}
