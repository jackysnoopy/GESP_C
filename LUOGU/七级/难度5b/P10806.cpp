#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n, m;
vector<long long> s, f;

bool can(long long K, vector<int>& assign) {
    vector<bool> used(n, false);
    int j = 0;

    for (int i = 0; i < m; i++) {
        // Find leftmost sprinkler that can cover flower f[i]
        // Sprinkler at s[j] covers f[i] if s[j] - K <= f[i] <= s[j] + K

        // Advance j to first sprinkler that can potentially cover f[i]
        while (j < n && s[j] + K < f[i]) j++;

        bool covered = false;
        for (int k = j; k < n && s[k] - K <= f[i]; k++) {
            if (!used[k] && abs(s[k] - f[i]) <= K) {
                used[k] = true;
                if (s[k] <= f[i]) assign[k] = 1; // R
                else assign[k] = 0; // L
                covered = true;
                break;
            }
        }
        if (!covered) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    s.resize(n);
    f.resize(m);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < m; i++) cin >> f[i];

    // Check if impossible: each sprinkler can cover at most one flower if K=0
    // and flowers are at different positions from sprinklers

    // Binary search on K
    long long lo = 0, hi = 2e9, ans = -1;
    vector<int> tmp_assign(n);
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (can(mid, tmp_assign)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (ans == -1) {
        cout << -1 << "\n";
        return 0;
    }

    // Reconstruct assignment with ans as K
    vector<int> assign(n, -1);
    vector<bool> used(n, false);
    int j = 0;

    for (int i = 0; i < m; i++) {
        while (j < n && s[j] + ans < f[i]) j++;
        for (int k = j; k < n && s[k] - ans <= f[i]; k++) {
            if (!used[k] && abs(s[k] - f[i]) <= ans) {
                used[k] = true;
                if (s[k] <= f[i]) assign[k] = 1;
                else assign[k] = 0;
                break;
            }
        }
    }

    // Assign unassigned sprinklers (can be either direction)
    for (int i = 0; i < n; i++) {
        if (assign[i] == -1) assign[i] = 0; // default to L
    }

    cout << ans << "\n";
    string result;
    for (int i = 0; i < n; i++) {
        result += (assign[i] == 0 ? 'L' : 'R');
    }
    cout << result << "\n";

    return 0;
}
