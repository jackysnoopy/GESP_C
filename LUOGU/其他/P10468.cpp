#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long long ULL;
const int P = 131;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s; cin >> s;
    int n = s.size();
    vector<ULL> h(n + 1, 0), p(n + 1, 1);
    for (int i = 0; i < n; i++) {
        h[i+1] = h[i] * P + s[i];
        p[i+1] = p[i] * P;
    }
    
    auto get = [&](int l, int r) {
        return h[r] - h[l-1] * p[r-l+1];
    };
    
    int m; cin >> m;
    while (m--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (get(l1, r1) == get(l2, r2) ? "Yes" : "No") << "\n";
    }
    return 0;
}