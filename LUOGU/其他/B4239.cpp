#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x0;
    cin >> n >> x0;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    if (n <= 1) { cout << 0 << "\n"; return 0; }
    sort(x.begin(), x.end());
    long long total = 0;
    for (int i = 0; i < n; i++) total += abs(x[i] - x0);
    long long best_skip = 0;
    for (int i = 0; i < n; i++) {
        long long cost_without = total - abs(x[i] - x0);
        best_skip = max(best_skip, total - cost_without);
    }
    cout << total - best_skip << "\n";
    return 0;
}
