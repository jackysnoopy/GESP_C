#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) cin >> r[i];
    // Classic candy problem (circular)
    // Left pass: if r[i] > r[i-1], candy[i] = candy[i-1] + 1
    // Right pass: if r[i] > r[i+1], candy[i] = max(candy[i], candy[i+1] + 1)
    // For circular: repeat until stable, or use a trick.
    // Since n <= 1e5, we can do 2 full passes (left and right) which handles linear case.
    // For circular, we need to handle the wrap-around.
    // Simple approach: run the algorithm twice (to handle circularity).
    vector<int> c(n, 1);
    // Left to right
    for (int i = 1; i < n; i++) {
        if (r[i] > r[i-1]) c[i] = c[i-1] + 1;
    }
    // Right to left (wrap around)
    for (int i = 0; i < n; i++) {
        int prev = (i - 1 + n) % n;
        int next = (i + 1) % n;
        if (r[prev] > r[i] && c[prev] <= c[i]) c[prev] = c[i] + 1;
    }
    // Multiple passes for circular convergence
    for (int iter = 0; iter < n; iter++) {
        bool changed = false;
        for (int i = 0; i < n; i++) {
            int prev = (i - 1 + n) % n;
            int next = (i + 1) % n;
            if (r[i] > r[prev] && c[i] <= c[prev]) { c[i] = c[prev] + 1; changed = true; }
            if (r[i] > r[next] && c[i] <= c[next]) { c[i] = c[next] + 1; changed = true; }
        }
        if (!changed) break;
    }
    long long total = 0;
    for (int i = 0; i < n; i++) total += c[i];
    cout << total << "\n";
    return 0;
}
