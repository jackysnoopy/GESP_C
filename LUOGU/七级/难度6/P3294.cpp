#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int MAXN = 510005;
int ch[MAXN][26], fail[MAXN], cnt, dfn[MAXN], sz[MAXN], dfntot;
long long ans;
void insert(string &s) {
    int p = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!ch[p][x]) ch[p][x] = ++cnt;
        p = ch[p][x];
    }
    dfn[p] = ++dfntot;
}
void build() {
    vector<int> q;
    for (int i = 0; i < 26; i++) if (ch[0][i]) q.push_back(ch[0][i]);
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        for (int j = 0; j < 26; j++) {
            if (ch[u][j]) {
                fail[ch[u][j]] = ch[fail[u]][j];
                q.push_back(ch[u][j]);
            } else {
                ch[u][j] = ch[fail[u]][j];
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];
    for (auto &w : words) reverse(w.begin(), w.end());
    for (auto &w : words) insert(w);
    build();
    cout << (long long)n * n << endl;
    return 0;
}