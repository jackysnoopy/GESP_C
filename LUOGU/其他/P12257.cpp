#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int ans = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && a[j] < 2 * a[i]) j++;
        if (j < n) { ans++; j++; }
    }
    cout << ans << "\n";
    return 0;
}
