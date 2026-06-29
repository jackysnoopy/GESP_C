#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 10000005;
int a[MAXN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    long long ans = 0;
    long long cur = 0;
    long long best = 0;
    int zeros = 0;
    int used = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            cur++;
        } else if (a[i] == -1) {
            cur--;
        } else {
            zeros++;
            if (used < k) {
                cur++;
                used++;
            }
        }
        best = min(best, cur);
        ans = max(ans, cur - best);
        if (cur == best) {
            zeros = 0;
            used = 0;
        }
    }
    printf("%lld\n", ans);
    return 0;
}