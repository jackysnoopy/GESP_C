#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) cin >> pos[i];
    vector<int> target(n + 1);
    for (int i = 1; i <= n; i++) target[pos[i]] = i;
    int ans = 0;
    int maxSeen = 0;
    for (int i = n; i >= 1; i--) {
        if (target[i] > maxSeen) {
            maxSeen = target[i];
            ans++;
        }
    }
    cout << n - ans << "\n";
    return 0;
}
