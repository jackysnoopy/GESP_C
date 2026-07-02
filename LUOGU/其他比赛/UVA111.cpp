#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> correct(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> correct[i];
        pos[correct[i]] = i;
    }
    vector<int> student(n + 1);
    int x;
    while (cin >> x) {
        student[1] = x;
        for (int i = 2; i <= n; i++) cin >> student[i];
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) a[i] = pos[student[i]];
        vector<int> dp(n + 1, 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < i; j++)
                if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
        cout << ans << "\n";
    }
    return 0;
}
