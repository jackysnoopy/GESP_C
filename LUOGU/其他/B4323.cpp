#include <iostream>
using namespace std;
typedef long long ll;

const int MAXN = 100005;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        char ch[MAXN];
        ll ln[MAXN];
        for (int i = 0; i < n; i++) cin >> ch[i] >> ln[i];
        bool allSame = true;
        for (int i = 1; i < n; i++) {
            if (ch[i] != ch[0]) { allSame = false; break; }
        }
        if (allSame) { cout << "-1\n"; continue; }
        
        // Greedy: cut shortest non-palindromic prefix repeatedly
        // rem[i] = remaining length in run i
        ll rem[MAXN];
        for (int i = 0; i < n; i++) rem[i] = ln[i];
        
        ll ans = 0;
        int ri = 0;
        bool stuck = false;
        
        while (ri < n) {
            // Skip empty runs
            while (ri < n && rem[ri] <= 0) { ri++; }
            if (ri >= n) break;
            
            ll left = rem[ri];
            
            if (left >= 2) {
                // In a run with >= 2 same chars
                if (ri == n - 1) { stuck = true; break; }
                // Cut: all of run ri + 1 from run ri+1
                // Piece chars: ch[ri] repeated left times + ch[ri+1]
                // First char = ch[ri], last char = ch[ri+1], they differ -> non-palindromic
                ans++;
                rem[ri] = 0;
                ri++;
                if (ri < n) {
                    rem[ri]--;
                    if (rem[ri] <= 0) { ri++; }
                }
            } else {
                // left == 1, at boundary
                if (ri == n - 1) { stuck = true; break; }
                // Cut: ch[ri] + ch[ri+1] (they differ) -> non-palindromic
                ans++;
                rem[ri] = 0;
                ri++;
                if (ri < n) {
                    rem[ri]--;
                    if (rem[ri] <= 0) { ri++; }
                }
            }
        }
        
        if (stuck) {
            cout << "-1\n";
        } else {
            cout << ans << "\n";
        }
    }
    return 0;
}
