#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> k(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> s_seq(m), t_seq(m);
    int pos = 0;
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i + 1;
    sort(order.begin(), order.end(), [&](int x, int y) {
        if (a[x] != a[y]) return a[x] > a[y];
        return x < y;
    });
    for (int idx : order) {
        int passes = a[idx];
        int was = k[idx];
        if (passes == 0) continue;
        int wa_per_pass = was / passes;
        int wa_extra = was % passes;
        int wa_so_far = 0;
        for (int j = 0; j < passes; j++) {
            int this_wa = wa_per_pass + (j < wa_extra ? 1 : 0);
            s_seq[pos] = idx;
            t_seq[pos] = wa_so_far;
            wa_so_far += this_wa;
            pos++;
        }
    }
    for (int i = 0; i < m; i++) {
        if (i) cout << " ";
        cout << s_seq[i];
    }
    cout << "\n";
    for (int i = 0; i < m; i++) {
        if (i) cout << " ";
        cout << t_seq[i];
    }
    cout << "\n";
    return 0;
}
