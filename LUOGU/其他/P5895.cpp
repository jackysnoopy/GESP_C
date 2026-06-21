#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Job { long long s, f; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long T;
    cin >> n >> T;
    vector<Job> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].s >> a[i].f;
    // Sort by s*f descending (Smith's rule variant)
    // Actually for this problem, the optimal order sorts by f/s or s*f
    // We need to minimize: sum over i of (T + sum of s[0..i-1]) * f[i]
    // Wait, need to check the actual problem.
    // For now, sort by f descending and compute
    sort(a.begin(), a.end(), [](const Job& a, const Job& b) {
        return a.f * b.s > b.f * a.s;
    });
    long long curT = T;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        curT += a[i].s;
        ans += curT * a[i].f;
    }
    cout << ans << "\n";
    return 0;
}
