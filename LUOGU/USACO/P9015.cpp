#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] > 0) sum += A[i];
        else sum -= A[i];
        if (i % 2 == 0) cout << 'R';
        else cout << 'L';
    }
    cout << '\n';
    return 0;
}
