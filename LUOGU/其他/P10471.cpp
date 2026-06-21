#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005 * 31;
int trie[MAXN][2], tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (!trie[p][b]) trie[p][b] = ++tot;
        p = trie[p][b];
    }
}

int query(int x) {
    int p = 1, res = 0;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (trie[p][b ^ 1]) {
            res |= (1 << i);
            p = trie[p][b ^ 1];
        } else {
            p = trie[p][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        insert(a[i]);
    }
    
    int ans = 0;
    for (int x : a) ans = max(ans, query(x));
    cout << ans << "\n";
    return 0;
}