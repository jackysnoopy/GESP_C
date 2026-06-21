#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Find minimum operations to make all equal
    // Each operation: a[i] = a[i] | a[j] for some j
    // If any element has all bits that any other has, we can make them equal
    // Answer: check if possible, then count bits
    long long common = a[0];
    for (int i = 1; i < n; i++) common &= a[i];
    for (int i = 0; i < n; i++) a[i] ^= common;
    long long total = 0;
    for (int i = 0; i < n; i++) total |= a[i];
    // Count set bits
    int bits = 0;
    for (int i = 0; i < 40; i++)
        if (total & (1LL<<i)) bits++;
    cout << bits << "\n";
    return 0;
}
