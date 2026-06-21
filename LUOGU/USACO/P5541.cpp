#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) cin >> pos[i];
    sort(pos.begin(), pos.end());
    if (n == 1) { cout << "0\n0\n"; return 0; }
    int mn = 0, mx = 0;
    for (int i = 1; i < n - 1; i++) {
        if (pos[i] != pos[i-1] + 1) mn++;
    }
    mx = max(pos[n-1] - pos[0] - n + 1 - (pos[1] - pos[0] - 1), 
             pos[n-1] - pos[0] - n + 1 - (pos[n-1] - pos[n-2] - 1));
    mx = max(mx, 0);
    for (int i = 1; i < n - 1; i++) {
        int leftGap = pos[i] - pos[i-1] - 1;
        int rightGap = pos[i+1] - pos[i] - 1;
        mx = max(mx, leftGap + rightGap - 1);
    }
    mx = max(mx, 0);
    cout << mn << "\n" << mx << "\n";
    return 0;
}
