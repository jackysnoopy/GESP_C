#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, L, v;
    cin >> n >> L >> v;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    vector<long long> cost(n);
    for (int i = 0; i < n; i++) {
        cost[i] = (long long)a[i] * 2 / v;
    }
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + cost[i];
    int q;
    cin >> q;
    while (q--) {
        long long t;
        cin >> t;
        long long baseTime = (long long)L * 2 / v;
        if (baseTime > t) { cout << "0\n"; continue; }
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            long long totalTime = baseTime + prefix[mid];
            if (totalTime > t) hi = mid;
            else lo = mid + 1;
        }
        if (lo == n) cout << "-1\n";
        else cout << lo << "\n";
    }
    return 0;
}
