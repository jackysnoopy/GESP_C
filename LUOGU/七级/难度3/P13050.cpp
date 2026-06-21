#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<tuple<int,int,int>> act(N);
        for (int i = 0; i < N; i++) {
            int s, e;
            cin >> s >> e;
            act[i] = {s, e, i};
        }
        sort(act.begin(), act.end());
        int cEnd = 0, jEnd = 0;
        string ans(N, ' ');
        bool ok = true;
        for (auto& [s, e, idx] : act) {
            if (s >= cEnd) { ans[idx] = 'C'; cEnd = e; }
            else if (s >= jEnd) { ans[idx] = 'J'; jEnd = e; }
            else { ok = false; break; }
        }
        cout << "Case #" << tc << ": ";
        if (ok) cout << ans << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}
