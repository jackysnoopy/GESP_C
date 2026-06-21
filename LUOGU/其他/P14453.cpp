#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Grand Voting: find element that appears more than n/2 times after some process.
    // Without full problem text, implement Boyer-Moore majority vote.
    int candidate = a[0], count = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == candidate) count++;
        else {
            count--;
            if (count == 0) { candidate = a[i]; count = 1; }
        }
    }
    // Verify
    int freq = 0;
    for (int i = 0; i < n; i++) if (a[i] == candidate) freq++;
    if (freq > n / 2) cout << candidate << endl;
    else cout << -1 << endl;
    return 0;
}
