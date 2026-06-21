#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> dif(m + 5, 0);
    while (n--) {
        int v, x;
        cin >> v >> x;
        int l1 = max(1, x - 3*v + 1), r1 = x - 2*v;
        int l2 = max(1, x - 2*v + 1), r2 = x;
        int l3 = max(1, x + 1), r3 = min(m, x + 2*v);
        int l4 = max(1, x + 2*v + 1), r4 = min(m, x + 3*v - 1);
        if (l1 <= r1) { dif[l1] += 1; dif[r1+1] -= 1; }
        if (l2 <= r2) { dif[l2] -= 1; dif[r2+1] += 1; }
        if (l3 <= r3) { dif[l3] -= 1; dif[r3+1] += 1; }
        if (l4 <= r4) { dif[l4] += 1; dif[r4+1] -= 1; }
    }
    for (int i = 1; i <= m; i++) {
        dif[i] += dif[i-1];
        cout << dif[i] << " \n"[i == m];
    }
    return 0;
}
