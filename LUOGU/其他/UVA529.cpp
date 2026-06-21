#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> best;
bool found;

void dfs(vector<int>& seq, int sum, int last) {
    if (found) return;
    if (sum == n) {
        if ((int)seq.size() < (int)best.size()) best = seq;
        found = true;
        return;
    }
    if (sum > n) return;
    if ((int)seq.size() >= (int)best.size() - 1) return;
    for (int v = last + 1; v <= n - sum; ++v) {
        seq.push_back(v);
        dfs(seq, sum + v, v);
        seq.pop_back();
        if (found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << '\n';
        first = false;
        best.clear();
        for (int len = 1; len <= n; ++len) {
            best.resize(len + 1);
            for (int i = 0; i <= len; ++i) best[i] = n + 1;
            found = false;
            vector<int> seq;
            dfs(seq, 0, 0);
            if (found) break;
        }
        for (int i = 0; i < (int)best.size(); ++i) {
            if (i) cout << ' ';
            cout << best[i];
        }
        cout << '\n';
    }
    return 0;
}
