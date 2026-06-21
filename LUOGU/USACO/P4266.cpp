#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L, N, rF, rB;
    cin >> L >> N >> rF >> rB;
    vector<pair<int,int>> stops(N);
    for (int i = 0; i < N; i++) {
        cin >> stops[i].first >> stops[i].second;
    }
    sort(stops.begin(), stops.end());
    long long ans = 0;
    int prevPos = 0;
    int maxTastiness = 0;
    for (int i = 0; i < N; i++) {
        int dist = stops[i].first - prevPos;
        long long timeSaved = (long long)dist * (rF - rB);
        ans += (long long)maxTastiness * timeSaved;
        maxTastiness = max(maxTastiness, stops[i].second);
        prevPos = stops[i].first;
    }
    cout << ans << "\n";
    return 0;
}
