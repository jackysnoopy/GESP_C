#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    // Each cow must fit in a stall (cow height <= stall limit).
    // Sort both. For each stall (ascending), count how many cows fit.
    // Multiply choices together.
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    long long ans = 1;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && a[j] <= b[i]) j++;
        // j cows can fit in stall i+1 (or rather, j choices including already taken)
        ans *= (j - i);
    }
    cout << ans << "\n";
    return 0;
}
