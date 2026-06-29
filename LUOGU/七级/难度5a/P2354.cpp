#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;
int n, m, q;
ll T[MAXN * MAXN];
int pos[MAXN * MAXN];
int row[MAXN * MAXN], col[MAXN * MAXN];

void gen_permutation(ll x0, ll a, ll b, ll c, ll d, int K) {
    for (int i = 1; i <= K; i++) T[i] = i;
    
    ll x = x0;
    for (int i = 1; i <= K; i++) {
        x = (a * x % d * x % d + b * x % d + c) % d;
        int j = (int)(x % i) + 1;
        swap(T[i], T[j]);
    }
}

int main() {
    ll x0, a, b, c, d;
    scanf("%lld%lld%lld%lld%lld", &x0, &a, &b, &c, &d);
    scanf("%d%d%d", &n, &m, &q);
    
    int K = n * m;
    gen_permutation(x0, a, b, c, d, K);
    
    for (int i = 1; i <= q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        swap(T[u], T[v]);
    }
    
    for (int i = 1; i <= K; i++) {
        pos[T[i]] = i;
        row[i] = (i - 1) / m + 1;
        col[i] = (i - 1) % m + 1;
    }
    
    vector<pair<int, int>> cells;
    for (int i = 1; i <= K; i++) {
        cells.push_back({(int)T[i], i});
    }
    sort(cells.begin(), cells.end());
    
    vector<int> ans;
    int curRow = 1, curCol = 1;
    
    for (auto& p : cells) {
        int val = p.first;
        int idx = p.second;
        int r = row[idx], c = col[idx];
        
        if (r >= curRow && c >= curCol) {
            ans.push_back(val);
            curRow = r;
            curCol = c;
            if (ans.size() == n + m - 1) break;
        }
    }
    
    for (int i = 0; i < (int)ans.size(); i++) {
        printf("%d%c", ans[i], i + 1 == (int)ans.size() ? '\n' : ' ');
    }
    
    return 0;
}
