#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> d(N);
    for (int i = 0; i < N; i++) cin >> d[i];
    int jumps = 1;
    int pos = 0;
    for (int i = 0; i < N; i++) {
        if (d[i] - pos <= M) continue;
        jumps++;
        pos = d[i - 1];
    }
    if (L - d[N - 1] > M) {
        jumps++;
    }
    cout << jumps << "\n";
    return 0;
}
