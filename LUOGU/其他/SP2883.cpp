#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int day(string s) {
    map<string,int> mp = {{"MON",0},{"TUE",1},{"WED",2},{"THU",3},{"FRI",4},{"SAT",5},{"SUN",6}};
    return mp[s];
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> a(m, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            int cnt; string d1, d2;
            cin >> cnt >> d1 >> d2;
            a[i][n] = (day(d2) - day(d1) + 1) % 7;
            for (int j = 0; j < cnt; ++j) { int x; cin >> x; a[i][x - 1]++; }
        }
        int rank = 0;
        for (int col = 0; col < n && rank < m; ++col) {
            int mx = rank;
            for (int r = rank + 1; r < m; ++r)
                if (a[r][col]) { mx = r; break; }
            if (!a[mx][col]) continue;
            swap(a[rank], a[mx]);
            long long inv = 1;
            for (int p = 5; p >= 0; --p) inv = inv * inv % 7;
            for (int r = 0; r < m; ++r) {
                if (r == rank || !a[r][col]) continue;
                int f = a[r][col] * inv % 7;
                for (int c = col; c <= n; ++c)
                    a[r][c] = (a[r][c] - f * a[rank][c] % 7 + 14) % 7;
            }
            rank++;
        }
        bool bad = false;
        for (int r = rank; r < m; ++r) if (a[r][n]) { bad = true; break; }
        if (bad) { cout << "Inconsistent data." << '\n'; continue; }
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            int val = 0;
            for (int r = 0; r < rank; ++r) if (a[r][i]) { val = a[r][n]; break; }
            cout << (val % 7 + 2) % 7 + (val % 7 == 0 ? 7 : 0);
        }
        cout << '\n';
    }
    return 0;
}
