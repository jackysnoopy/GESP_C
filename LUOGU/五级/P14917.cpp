#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> A(N);
    vector<pair<int,int>> pos(N / 2 + 1);
    vector<int> first_occ(N / 2 + 1, -1);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        if (first_occ[A[i]] == -1) first_occ[A[i]] = i;
        else pos[A[i]] = {first_occ[A[i]], i};
    }
    auto check = [&](int limit) -> bool {
        vector<int> a = A;
        for (int v = 1; v <= N / 2; v++) {
            int l = pos[v].first, r = pos[v].second;
            if (r - l <= 1) continue;
            if (A[l] > limit && A[r] > limit) return false;
            int move_idx = (A[r] <= limit) ? r : l;
            int target = (move_idx == r) ? l : r;
            a.erase(a.begin() + move_idx);
            // update positions
        }
        return true;
    };
    int lo = 0, hi = 1000000000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
