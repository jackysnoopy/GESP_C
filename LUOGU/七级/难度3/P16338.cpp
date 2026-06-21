#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cards(n);
    for (int i = 0; i < n; i++) cin >> cards[i];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= cards[i];
    }

    cout << (ans == 0 ? 0 : 1) << "\n";
    return 0;
}
