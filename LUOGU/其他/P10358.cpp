#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long d_arr[35];
int N;
long long solve(long long hh, long long ww, int idx) {
    if (hh == 0 || ww == 0) return 0;
    if (idx < 0) return -1;
    long long dv = d_arr[idx];
    long long cnt = (hh / dv) * (ww / dv);
    long long rh = hh % dv;
    long long rw = ww % dv;
    long long s1 = solve(rh, ww, idx - 1);
    if (s1 == -1) return -1;
    long long s2 = solve(hh, rw, idx - 1);
    if (s2 == -1) return -1;
    long long s3 = solve(rh, rw, idx - 1);
    if (s3 == -1) return -1;
    return cnt + s1 + s2 - s3;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long h, w; cin >> h >> w >> N;
    for (int i = 0; i < N; i++) cin >> d_arr[i];
    long long ans = solve(h, w, N - 1);
    cout << ans << "\n";
    return 0;
}
