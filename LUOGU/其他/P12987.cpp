#include <iostream>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        deque<int> dq(N);
        for (int i = 0; i < N; i++) cin >> dq[i];
        int ans = 0;
        int cur = 0;
        while (!dq.empty()) {
            int left = dq.front(), right = dq.back();
            int pick = (left < right) ? left : right;
            if (pick >= cur) {
                ans++;
                cur = pick;
            }
            if (left <= right) dq.pop_front();
            else dq.pop_back();
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
