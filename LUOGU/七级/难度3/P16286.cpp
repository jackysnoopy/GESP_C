#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;

    vector<int> voltages(n);
    for (int i = 0; i < n; i++) cin >> voltages[i];

    int ans = 0;
    for (int x : voltages) {
        if (x > v) ans++;
    }

    cout << ans << "\n";
    return 0;
}
