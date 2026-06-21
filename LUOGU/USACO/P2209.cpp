#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, G, B, D;
    cin >> N >> G >> B >> D;
    vector<pair<int,int>> stations(N);
    for (int i = 0; i < N; i++) cin >> stations[i].first >> stations[i].second;
    stations.push_back({D, 0});
    sort(stations.begin(), stations.end());
    long long cost = 0;
    int curFuel = B;
    for (int i = 0; i <= N; i++) {
        int dist = (i == 0 ? stations[0].first : stations[i].first - stations[i-1].first);
        curFuel -= dist;
        if (curFuel < 0) { cout << -1 << endl; return 0; }
        if (i < N) {
            int need = G - curFuel;
            if (need > 0) {
                cost += (long long)need * stations[i].second;
                curFuel = G;
            }
        }
    }
    cout << cost << endl;
    return 0;
}