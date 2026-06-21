#include <iostream>
using namespace std;

// [MtOI2019] 永夜的报应
// Key insight: XOR of all elements is invariant under grouping.
// If total XOR is 0, answer is 0 (put all in one group).
// Otherwise, answer is the total XOR itself.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        total ^= x;
    }
    cout << total << "\n";
    return 0;
}
