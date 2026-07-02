#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 3000005;
int a[MAXN], fa[MAXN];
long long ans = 0;
int op, n, seed;

int Rand(int x) {
    seed = (1ll * seed * 0x66CCF + 19260817ll) % x + 1;
    seed = (1ll * seed * 0x77CCF + 20060428ll) % x + 1;
    seed = (1ll * seed * 0x88CCF + 12345678ll) % x + 1;
    seed = (1ll * seed * 0x33CCCCFF + 10086001ll) % x + 1;
    return seed;
}

void solve() {
    if (op == 1) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            fa[v] = u;
        }
    } else {
        scanf("%d %d", &seed, &n);
        for (int i = 1; i <= n; i++) a[i] = Rand(1000000000);
        for (int i = 2; i <= n; i++) fa[i] = Rand(i - 1);
    }
    
    // 从叶子向上贪心
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i + 1;
    sort(order.begin(), order.end(), [](int x, int y) { return x > y; });
    
    for (int u : order) {
        if (u == 1) continue;
        if (a[u] > 0) {
            ans += a[u];
            a[fa[u]] += a[u];
        } else if (a[u] < 0) {
            ans -= a[u];
            a[fa[u]] += a[u];
        }
    }
    ans += abs(a[1]);
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &op);
    solve();
    return 0;
}