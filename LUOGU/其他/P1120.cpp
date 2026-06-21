#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;
int total, stick_len, cnt;
bool found;

void dfs(int idx, int cur_len, int used) {
    if (found) return;
    if (used == cnt) { found = true; return; }
    if (cur_len == stick_len) { dfs(0, 0, used + 1); return; }
    int last = -1;
    for (int i = idx; i < n; ++i) {
        if (a[i] < 0) continue;
        if (a[i] == last) continue;
        if (cur_len + a[i] > stick_len) continue;
        last = a[i];
        int val = a[i];
        a[i] = -a[i];
        dfs(i + 1, cur_len + val, used);
        a[i] = -a[i];
        if (found) return;
        if (cur_len == 0) return;
        if (cur_len + val == stick_len) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    a.resize(n);
    total = 0;
    int maxv = 0;
    for (int i = 0; i < n; ++i) { cin >> a[i]; total += a[i]; maxv = max(maxv, a[i]); }
    sort(a.begin(), a.end(), greater<int>());
    for (stick_len = maxv; stick_len <= total; ++stick_len) {
        if (total % stick_len != 0) continue;
        cnt = total / stick_len;
        found = false;
        dfs(0, 0, 0);
        if (found) { cout << stick_len << '\n'; return 0; }
    }
    cout << total << '\n';
    return 0;
}
