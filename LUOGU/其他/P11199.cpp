#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, D;
    cin >> N >> D;
    int A[200];
    for (int i = 0; i < 2 * N; i++) cin >> A[i];
    sort(A, A + 2 * N);
    // Pair consecutive elements after sorting: A[0]-A[1], A[2]-A[3], ...
    // This is optimal for minimizing max difference.
    for (int i = 0; i < N; i++) {
        if (A[2 * i + 1] - A[2 * i] > D) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}
