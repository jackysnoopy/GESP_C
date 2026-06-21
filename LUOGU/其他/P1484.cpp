#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    struct Node { long long val; int id; bool operator<(const Node& o) const { return val < o.val; } };
    priority_queue<Node> pq;
    vector<int> left(n), right(n);
    vector<bool> removed(n, false);
    for (int i = 0; i < n; i++) { pq.push({a[i], i}); left[i] = i-1; right[i] = i+1; }
    long long ans = 0; int cnt = 0;
    while (cnt < k) {
        Node top = pq.top(); pq.pop();
        if (removed[top.id]) continue;
        if (top.val < 0) break;
        ans += top.val; cnt++;
        int l = left[top.id], r = right[top.id];
        if (l >= 0 && r < n) {
            long long nv = a[l] + a[r] - a[top.id];
            a[top.id] = nv;
            pq.push({nv, top.id});
            removed[l] = true; removed[r] = true;
            left[top.id] = left[l]; right[top.id] = right[r];
            if (left[top.id] >= 0) right[left[top.id]] = top.id;
            if (right[top.id] < n) left[right[top.id]] = top.id;
        } else {
            removed[top.id] = true;
            if (l >= 0) right[l] = r;
            if (r < n) left[r] = l;
        }
    }
    cout << ans << endl;
    return 0;
}