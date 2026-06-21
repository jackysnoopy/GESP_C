#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) cin >> r[i];
    sort(r.begin(), r.end());
    int ans = 0;
    int j = n / 2;
    for (int i = 0; i < n / 2; i++) {
        while (j < n && r[j] < 2 * r[i]) j++;
        if (j < n) { ans++; j++; }
    }
    cout << n / 2 - ans << "\n";
    return 0;
}
