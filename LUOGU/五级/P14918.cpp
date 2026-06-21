#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    map<int, vector<int>> pe;
    for (int x : A) {
        int t = x;
        for (int p = 2; p * p <= t; p++) {
            if (t % p == 0) {
                int e = 0;
                while (t % p == 0) { t /= p; e++; }
                pe[p].push_back(e);
            }
        }
        if (t > 1) pe[t].push_back(1);
    }
    long long ans = 0;
    for (auto &kv : pe) {
        auto &v = kv.second;
        sort(v.begin(), v.end());
        int med = v[v.size() / 2];
        for (int e : v) ans += abs(e - med);
        ans += med * (N - (int)v.size());
    }
    cout << ans << "\n";
    return 0;
}
