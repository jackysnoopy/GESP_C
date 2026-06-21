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
    // Simple game: first player wins if XOR of all a[i] != 0
    int xr = 0;
    for (int i = 0; i < n; i++) xr ^= a[i];
    cout << (xr != 0 ? "Yes" : "No") << "\n";
    return 0;
}
