#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> harvest(n);
    for (int i = 0; i < n; i++) cin >> harvest[i];

    int ans = 0;
    for (int h : harvest) ans += h;

    cout << ans << "\n";
    return 0;
}
