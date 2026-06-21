#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) cin >> A[i] >> B[i];

    int K;
    cin >> K;

    for (int q = 0; q < K; q++) {
        int n1, n2;
        cin >> n1 >> n2;
        n1--; n2--;

        bool found = false;
        for (int i = n1; i < n2 && !found; i++) {
            for (int j = i + 1; j <= n2 && !found; j++) {
                if (A[i] != A[j] && A[i] != B[j] && B[i] != A[j] && B[i] != B[j]) {
                    cout << i + 1 << " " << j + 1 << "\n";
                    found = true;
                }
            }
        }

        if (!found) cout << "0 0\n";
    }

    return 0;
}
