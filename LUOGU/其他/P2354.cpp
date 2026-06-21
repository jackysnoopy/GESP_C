#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, M, Q;
    long long x0, a, b, c, d;
    cin >> N >> M >> x0 >> a >> b >> c >> d >> Q;
    vector<long long> T(N*M+1);
    for (int i = 1; i <= N*M; i++) T[i] = i;
    long long xi = x0;
    for (int i = 1; i <= N*M; i++) {
        xi = (a * xi % d * xi % d + b * xi % d + c) % d;
        int j = (xi % i) + 1;
        swap(T[i], T[j]);
    }
    for (int i = 1; i <= Q; i++) {
        long long ui, vi;
        cin >> ui >> vi;
        swap(T[ui], T[vi]);
    }
    int r = 1, c_idx = 1;
    for (int i = 1; i <= N*M; i++) {
        int tr = (i-1)/M+1, tc = (i-1)%M+1;
        if (T[i] < T[r]) { r = i; c_idx = tc; }
    }
    cout << T[r] << endl;
    return 0;
}