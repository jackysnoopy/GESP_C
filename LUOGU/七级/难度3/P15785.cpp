#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, mod;
    cin >> n >> mod;

    int maxMod = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        maxMod = max(maxMod, x % mod);
    }

    cout << maxMod << "\n";
    return 0;
}
