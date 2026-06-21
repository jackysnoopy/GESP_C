#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    long long cur = 0, ans = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cur = max((long long)x, cur + x);
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}