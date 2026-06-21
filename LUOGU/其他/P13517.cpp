#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> X(N);
    for (int i = 0; i < N; i++) cin >> X[i];
    long long ans = 0;
    int cur = 0;
    for (int i = 0; i < N; i++) {
        int target = X[i] - 1;
        int dist = target - cur;
        if (dist < 0) { cout << -1 << endl; return 0; }
        ans += (dist + 1) / 2 + 1;
        cur = X[i] + 1;
    }
    cout << ans << endl;
    return 0;
}
