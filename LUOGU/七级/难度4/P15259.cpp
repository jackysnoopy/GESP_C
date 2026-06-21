#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    set<int> S(A.begin(), A.end());
    int distinct = S.size();

    vector<int> ans(N);

    for (int j = 0; j < N; j++) {
        set<int> seen;
        int ops = 0;
        int cur = j;

        while (seen.size() < distinct) {
            seen.insert(A[cur]);
            ops++;
            cur = (cur + 1) % N;
        }

        ans[j] = ops;
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}
