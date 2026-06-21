#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> p(N), t(N);
    for (int i = 0; i < N; i++) cin >> p[i];
    for (int i = 0; i < N; i++) cin >> t[i];
    vector<int> diff(N);
    for (int i = 0; i < N; i++) diff[i] = p[i] - t[i];
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            ans += abs(diff[i]);
        } else {
            if (diff[i] > 0 && diff[i-1] > 0) {
                ans += max(0, diff[i] - diff[i-1]);
            } else if (diff[i] < 0 && diff[i-1] < 0) {
                ans += max(0, -diff[i] - (-diff[i-1]));
            } else {
                ans += abs(diff[i]);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
