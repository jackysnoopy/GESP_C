#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> subjects(n);
    for (int i = 0; i < n; i++) cin >> subjects[i];

    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans = max(ans, abs(subjects[i] - subjects[i-1]));
    }

    cout << ans << "\n";
    return 0;
}
