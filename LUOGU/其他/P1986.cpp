#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int>> con(m);
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        con[i] = make_tuple(a, b, c);
    }
    sort(con.begin(), con.end(), [](const tuple<int,int,int>& a, const tuple<int,int,int>& b) {
        return get<1>(a) < get<1>(b);
    });
    vector<int> mic(n + 2, 0);
    int ans = 0;
    for (int ii = 0; ii < m; ii++) {
        int a = get<0>(con[ii]), b = get<1>(con[ii]), c = get<2>(con[ii]);
        int have = 0;
        for (int i = a; i <= b; i++) have += mic[i];
        if (have < c) {
            for (int i = b; i >= a && have < c; i--) {
                if (mic[i] == 0) { mic[i] = 1; have++; ans++; }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
