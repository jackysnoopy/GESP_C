#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        a[i] = (c == 'B') ? 1 : 0;
    }
    int bestK = 1, bestM = n;
    for (int k = 1; k <= n; k++) {
        vector<int> flip(n, 0);
        int cnt = 0;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (i >= k) sum -= flip[i-k];
            int cur = a[i] ^ (sum & 1);
            if (cur == 1) {
                if (i+k > n) { cnt = n+1; break; }
                flip[i] = 1;
                sum++;
                cnt++;
            }
        }
        if (cnt < bestM) { bestM = cnt; bestK = k; }
    }
    cout << bestK << " " << bestM << "\n";
    return 0;
}
