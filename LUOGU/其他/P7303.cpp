#include <iostream>
#include <vector>
using namespace std;

// [COCI 2018/2019 #1] Nadan
// Assign 1, 2, ..., N-1 to first N-1 projects, last project gets K - sum(1..N-1)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long K;
    int N;
    cin >> K >> N;
    long long sum = (long long)N * (N - 1) / 2;
    for (int i = 1; i < N; i++) {
        cout << i << "\n";
    }
    cout << K - sum << "\n";
    return 0;
}
