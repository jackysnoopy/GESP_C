#include <iostream>
#include <algorithm>
using namespace std;
int n;
long long x;
int h[100001];
long long pre[100001];
bool check(long long y) {
    // For each window of size y, sum of h in that window must be >= 2x
    // Windows are: [1, y], [2, y+1], ..., [n-1-y+1, n-1]
    // i.e., for start s from 1 to n-1-y+1 = n-y
    // sum of h[s..s+y-1] >= 2x
    for (int s = 1; s + y - 1 <= n - 1; s++) {
        long long sum = pre[s + y - 1] - pre[s - 1];
        if (sum < 2 * x) return false;
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> x;
    pre[0] = 0;
    for (int i = 1; i <= n - 1; i++) {
        cin >> h[i];
        pre[i] = pre[i - 1] + h[i];
    }
    long long lo = 1, hi = n - 1;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
