#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // Each subsequence with mex != 0 must contain at least one 0.
    // Maximum number of subsequences = number of 0s.
    // Each 0 goes to its own subsequence, non-zeros distributed freely.
    int cnt0 = 0, x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x == 0) cnt0++;
    }
    cout << cnt0 << "\n";
    return 0;
}
