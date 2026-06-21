#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }
    // Choose interval [l,r], result = total + (k-1)*sum(a[l..r])
    // If k>=1, maximize sum(a[l..r]) via Kadane's algorithm
    long long maxSum = a[0], cur = a[0];
    for (int i = 1; i < n; i++) {
        cur = max(a[i], cur + a[i]);
        maxSum = max(maxSum, cur);
    }
    cout << total + (k - 1) * maxSum << endl;
    return 0;
}
