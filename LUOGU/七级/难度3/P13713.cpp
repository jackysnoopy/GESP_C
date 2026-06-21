#include <cstdio>
#include <vector>
using namespace std;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        int interior = n - 2; if (interior < 0) interior = 0;
        if (x + y > interior) { printf("-2\n"); continue; }
        vector<int> a(n + 1, 0);
        if (x > 0) {
            if (x % 2 == 0) {
                for (int k = 1; k <= x / 2; k++) a[2 * k] = 1;
            } else {
                for (int k = 0; k <= x / 2; k++) a[2 * k + 1] = 1;
            }
        }
        if (y > 0) {
            if (y == 1) {
                a[n] = -1;
            } else if (y % 2 == 0) {
                for (int k = 0; k < y / 2; k++) a[n - 1 - 2 * k] = -1;
            } else {
                for (int k = 0; k < (y - 1) / 2; k++) a[n - 2 - 2 * k] = -1;
            }
        }
        bool conflict = false;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1 && a[i] == -1) { conflict = true; break; }
        }
        int sc = 0, cc = 0;
        for (int i = 2; i <= n - 1; i++) {
            int s = a[i-1] + a[i] + a[i+1];
            if (s >= 1 && s <= 2) sc++;
            else if (s >= -2 && s <= -1) cc++;
        }
        if (sc == x && cc == y) {
            for (int i = 1; i <= n; i++) printf("%d%c", a[i], i < n ? ' ' : '\n');
        } else {
            printf("-2\n");
        }
    }
    return 0;
}
