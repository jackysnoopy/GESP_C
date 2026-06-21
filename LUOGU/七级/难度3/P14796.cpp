#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dangos(n);
    for (int i = 0; i < n; i++) cin >> dangos[i];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dangos[i] > ans) ans = dangos[i];
    }

    cout << ans << "\n";
    return 0;
}
