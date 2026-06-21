#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Pour x into x+1, at most k times => can merge any k+1 consecutive into one
    // prefix sums
    vector<long long> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i+1] = pre[i] + a[i];
    long long ans = 0;
    int w = (int)min((long long)n, k + 1);
    for (int i = 0; i + w <= n; i++) {
        ans = max(ans, pre[i + w] - pre[i]);
    }
    cout << ans << "\n";
    return 0;
}
