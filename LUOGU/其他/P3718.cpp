#include <iostream>
#include <string>
using namespace std;
int n, k;
string s;
bool check(int mid) {
    int cnt = 0, i = 0;
    while (i < n) {
        if (s[i] == 'N') {
            cnt++;
            i += mid + 1;
        } else i++;
    }
    return cnt <= k;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> s;
    int lo = 1, hi = n, ans = n;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (check(mid)) { ans = mid; hi = mid-1; }
        else lo = mid+1;
    }
    cout << ans << "\n";
    return 0;
}
