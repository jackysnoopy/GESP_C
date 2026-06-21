#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n);
    int pos1 = -1, posN = -1;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (x[i] == 1) pos1 = i;
        if (x[i] == n) posN = i;
    }
    int ans = pos1 + (n - 1 - posN);
    if (pos1 > posN) ans--;
    cout << ans << "\n";
    return 0;
}
