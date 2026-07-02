#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, k;
int cover[MAXN]; // cover[i]: 从位置i开始，能覆盖到的最远位置

int main() {
    scanf("%d%d", &n, &k);

    memset(cover, 0, sizeof(cover));

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a <= b) {
            cover[a] = max(cover[a], b);
        } else {
            cover[a] = max(cover[a], b + n);
            if (a + n > cover[a])
                cover[a] = b + n;
        }
    }

    int ans = INF;

    for (int start = 1; start <= n; start++) {
        int cnt = 0;
        int cur = start;
        int maxReach = start - 1;

        while (maxReach < start + n - 1) {
            cnt++;
            int nextMax = maxReach;

            for (int j = 1; j <= n; j++) {
                int pos = (start + j - 2) % n + 1;
                if (pos - 1 <= maxReach - start + 1) {
                    int reach = cover[pos];
                    if (reach > 0) {
                        int realReach = reach;
                        if (realReach < pos) realReach += n;
                        if (realReach - start > nextMax - start + 1)
                            nextMax = realReach;
                    }
                }
            }

            if (nextMax == maxReach - 1) {
                cnt = INF;
                break;
            }
            maxReach = nextMax;
        }

        ans = min(ans, cnt);
    }

    if (ans == INF)
        printf("impossible\n");
    else
        printf("%d\n", ans);

    return 0;
}
