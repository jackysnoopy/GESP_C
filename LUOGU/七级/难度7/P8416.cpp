#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> a[i][j];
    // pos[v] = (r,c) 当前位置 (v: 1..n*n)
    vector<int> pr(n * n + 1), pc(n * n + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) { pr[a[i][j]] = i; pc[a[i][j]] = j; }
    struct Op { int x1, y1, x2, y2; };
    vector<Op> ops;
    auto doSwap = [&](int r1, int c1, int r2, int c2) {
        // 合法性：同行或同列
        int v1 = a[r1][c1], v2 = a[r2][c2];
        a[r1][c1] = v2; a[r2][c2] = v1;
        pr[v1] = r2; pc[v1] = c2;
        pr[v2] = r1; pc[v2] = c1;
        ops.push_back({r1 + 1, c1 + 1, r2 + 1, c2 + 1});
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v = i * n + j + 1;
            if (a[i][j] == v) continue;
            int r = pr[v], c = pc[v];
            if (r == i) {
                // 同行：与 (i, c) 交换，c > j（前方已归位保证）
                doSwap(i, c, i, j);
            } else if (c == j) {
                // 同列：与 (r, j) 交换，r > i
                doSwap(r, j, i, j);
            } else {
                // 不同行不同列：先同行交换把 v 移到 (r, j)，再同列交换到 (i, j)
                doSwap(r, c, r, j);
                doSwap(r, j, i, j);
            }
        }
    }
    cout << ops.size() << "\n";
    for (const auto &op : ops)
        cout << op.x1 << " " << op.y1 << " " << op.x2 << " " << op.y2 << "\n";
    return 0;
}
