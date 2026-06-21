#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> L(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) { cin >> L[i]; sum += L[i]; }
    if (sum < k) { cout << 0 << "\n"; return 0; }
    long long lo = 1, hi = 1e9;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        long long cnt = 0;
        for (int i = 0; i < n; i++) cnt += L[i] / mid;
        if (cnt >= k) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
