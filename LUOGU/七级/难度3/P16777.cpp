#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; i++) cin >> scores[i];

    int ans = 0;
    for (int s : scores) ans += s;

    cout << ans << "\n";
    return 0;
}
