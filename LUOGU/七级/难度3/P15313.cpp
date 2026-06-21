#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> spells(n);
    for (int i = 0; i < n; i++) cin >> spells[i];

    int ans = 0;
    for (int s : spells) ans ^= s;

    cout << ans << "\n";
    return 0;
}
