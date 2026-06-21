#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1000005;
int trie[MAXN][26], cnt[MAXN], tot = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        int p = 1;
        for (char c : s) {
            int idx = c - 'a';
            if (!trie[p][idx]) trie[p][idx] = ++tot;
            p = trie[p][idx];
            cnt[p]++;
        }
    }
    
    cin >> M;
    while (M--) {
        string s; cin >> s;
        int p = 1, ans = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!trie[p][idx]) { ans = 0; break; }
            p = trie[p][idx];
            ans = cnt[p];
        }
        cout << ans << "\n";
    }
    return 0;
}