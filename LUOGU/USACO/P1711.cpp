#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // a[i] = number of days since last outbreak (0 = outbreak day)
    // Count minimum and maximum outbreaks
    int minOut = 0, maxOut = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) { minOut++; maxOut++; }
        else if (a[i] == -1) { maxOut++; }
    }
    // Actually for -1 (unknown), it could be outbreak or not
    // For known 0: definitely outbreak
    // For known > 0: definitely not outbreak
    // The minimum outbreaks = count of known 0s
    // The maximum outbreaks = count of (known 0s) + count of (-1s)
    cout << minOut << " " << maxOut << "\n";
    return 0;
}
