#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<pair<long long,long long>> art(N);
    for (int i = 0; i < N; i++) {
        cin >> art[i].first >> art[i].second;
    }
    sort(art.begin(), art.end());
    vector<long long> suffix(N + 1, 0);
    for (int i = N - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + art[i].second;
    }
    long long ans = art[0].second;
    for (int i = 0; i < N; i++) {
        long long val = suffix[i] - (art[i].first - art[0].first);
        ans = max(ans, val);
    }
    cout << ans << "\n";
    return 0;
}
