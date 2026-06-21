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
    sort(a.begin(), a.end(), greater<int>());
    int ans = 0;
    int i = 0;
    while (i < n) {
        // Find team size: first person wants >= a[i], team needs at least a[i] people
        int need = a[i];
        if (i + need <= n) {
            ans++;
            i += need;
        } else break;
    }
    cout << ans << "\n";
    return 0;
}
