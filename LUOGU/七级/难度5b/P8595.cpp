#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 2000005;
int deg[MAXN];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        deg[u]++;
        deg[v]++;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 2) {
            ans += deg[i] - 2;
        }
    }
    ans += n - m - 1;
    printf("%lld\n", ans);
    return 0;
}