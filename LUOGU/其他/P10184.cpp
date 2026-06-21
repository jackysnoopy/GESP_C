#include <iostream>
#include <algorithm>
using namespace std;
int n, t;
long long a[500001];
bool check(long long d) {
    // Can we have d interesting days?
    // Each day needs at least t subjects, so we need d*t subject-day slots
    // Each subject i can contribute at most min(a_i, d) days
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += min(a[i], d);
    }
    return total >= d * t;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> t;
    long long sum = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; sum += a[i]; }
    long long lo = 0, hi = sum / t;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
