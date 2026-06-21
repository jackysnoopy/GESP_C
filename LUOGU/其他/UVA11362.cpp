#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 100005;
int trie[MAXN][10], tot;
bool end_mark[MAXN];

bool insert(const string& s) {
    int p = 0;
    for (char c : s) {
        int idx = c - '0';
        if (!trie[p][idx]) trie[p][idx] = ++tot;
        p = trie[p][idx];
        if (end_mark[p]) return false;
    }
    // 检查是否有号码是它的前缀
    for (int i = 0; i < 10; i++)
        if (trie[p][i]) return false;
    end_mark[p] = true;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        memset(trie, 0, sizeof(trie));
        memset(end_mark, 0, sizeof(end_mark));
        tot = 0;
        
        int n; cin >> n;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            if (ok && !insert(s)) ok = false;
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}