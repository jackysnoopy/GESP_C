#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 反悔贪心：双向链表 + 大根堆
// 每次取出当前最大获利的位置 p，加上其值；
// 然后将 a[p] 替换成 a[L[p]] + a[R[p]] - a[p]，并删除其左右邻居。
// 这样下次若选了这个"虚拟节点"，相当于撤销 p 改选 L[p] 和 R[p]。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    const long long NEG_INF = -1e18;
    vector<long long> a(n + 2);
    vector<int> L(n + 2), R(n + 2);
    a[0] = a[n + 1] = NEG_INF;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        L[i] = i - 1;
        R[i] = i + 1;
    }
    L[n + 1] = n;
    R[0] = 1;

    priority_queue<pair<long long, int>> pq;
    for (int i = 1; i <= n; i++) pq.push({a[i], i});

    vector<bool> removed(n + 2, false);
    long long ans = 0;
    for (int t = 0; t < k; t++) {
        while (!pq.empty() && (removed[pq.top().second] || pq.top().first != a[pq.top().second])) {
            pq.pop();
        }
        if (pq.empty()) break;
        auto [val, p] = pq.top();
        pq.pop();
        if (val <= 0) break;
        ans += val;
        int l = L[p], r = R[p];
        // 用 a[l] + a[r] - a[p] 取代 p
        a[p] = a[l] + a[r] - a[p];
        removed[l] = removed[r] = true;
        // 调整链表
        L[p] = L[l];
        R[p] = R[r];
        R[L[p]] = p;
        L[R[p]] = p;
        pq.push({a[p], p});
    }
    cout << ans << "\n";
    return 0;
}
