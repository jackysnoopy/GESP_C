#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<int> C(N+1);
    for (int i = 1; i <= N; i++) cin >> C[i];
    vector<pair<int,int>> requests(M);
    for (int i = 0; i < M; i++) cin >> requests[i].first >> requests[i].second;
    sort(requests.begin(), requests.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    int ans = 0;
    vector<int> cap(N+2, 0);
    for (int i = 0; i < M; i++) {
        int a = requests[i].first, b = requests[i].second;
        int mn = 1e9;
        for (int j = a; j <= b; j++) mn = min(mn, C[j] - cap[j]);
        if (mn > 0) {
            ans++;
            for (int j = a; j <= b; j++) cap[j]++;
        }
    }
    cout << ans << endl;
    return 0;
}