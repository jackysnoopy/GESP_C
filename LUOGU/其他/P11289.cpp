#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct File { int id, s, t; };
bool cmpTime(const File& a, const File& b) { return a.t < b.t; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    File f[200001];
    for (int i = 0; i < n; i++) { cin >> f[i].s >> f[i].t; f[i].id = i + 1; }
    sort(f, f + n, cmpTime);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 0; i < m; i++) pq.push(make_pair(0LL, i));
    vector<vector<int>> result(m);
    for (int i = 0; i < n; i++) {
        pair<long long, int> top = pq.top(); pq.pop();
        long long time = top.first;
        int pid = top.second;
        long long start = max(time, (long long)f[i].t);
        pq.push(make_pair(start + f[i].s, pid));
        result[pid].push_back(f[i].id);
    }
    for (int i = 0; i < m; i++) {
        sort(result[i].begin(), result[i].end());
        cout << result[i].size();
        for (int j = 0; j < (int)result[i].size(); j++) cout << " " << result[i][j];
        cout << "\n";
    }
    return 0;
}
