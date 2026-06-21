#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> melody(n);
    for (int i = 0; i < n; i++) cin >> melody[i];

    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (melody[i] > melody[i - 1]) ans++;
    }

    cout << ans << "\n";
    return 0;
}
