#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int n, maxI;
vector<vector<int>> results;
void dfs(vector<int>& vals, int pos) {
    if (pos == n) {
        set<int> sums;
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = 0; j < n; j++) {
                s += vals[(i + j) % n];
                sums.insert(s);
            }
        }
        int mx = 0;
        while (sums.count(mx + 1)) mx++;
        if (mx > maxI) { maxI = mx; results.clear(); results.push_back(vals); }
        else if (mx == maxI) results.push_back(vals);
        return;
    }
    for (int v = 1; v <= 9; v++) {
        vals[pos] = v;
        dfs(vals, pos + 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    maxI = 0;
    vector<int> vals(n);
    dfs(vals, 0);
    cout << maxI << "\n";
    vector<int> best;
    for (auto& r : results) {
        for (int i = 0; i < n; i++) {
            if (r[i] == 1) {
                vector<int> rot;
                for (int j = 0; j < n; j++) rot.push_back(r[(i + j) % n]);
                if (best.empty() || rot < best) best = rot;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) { if (i) cout << " "; cout << best[i]; }
    cout << "\n";
    return 0;
}
