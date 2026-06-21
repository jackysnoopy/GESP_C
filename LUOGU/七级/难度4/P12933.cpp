#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    long long k;
    cin >> n >> s >> k;

    vector<long long> d(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> d[i];

    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    vector<long long> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + d[i - 1];

    vector<int> left(n), right(n);
    for (int i = 0; i < n; i++) {
        left[i] = lower_bound(pos.begin(), pos.end(), pos[i] - k) - pos.begin();
        right[i] = upper_bound(pos.begin(), pos.end(), pos[i] + k) - pos.begin() - 1;
    }

    vector<long long> dp(n + 1, 0);
    vector<int> use(n, 0);

    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i];
        long long sum = 0;
        for (int j = i; j >= left[i]; j--) {
            sum += v[j];
            if (dp[j] + sum > dp[i + 1]) {
                dp[i + 1] = dp[j] + sum;
                use[i] = j;
            }
        }
    }

    vector<int> shields;
    int cur = n - 1;
    while (cur >= 0) {
        if (use[cur] > 0 || dp[cur + 1] > dp[cur]) {
            shields.push_back(cur);
            cur = use[cur] - 1;
        } else {
            cur--;
        }
    }

    reverse(shields.begin(), shields.end());

    cout << shields.size() << "\n";
    for (int i = 0; i < (int)shields.size(); i++) {
        if (i) cout << " ";
        cout << shields[i] + 1;
    }
    cout << "\n";

    return 0;
}
