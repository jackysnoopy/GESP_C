#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    // A[i] must satisfy: B[i] = max(A[0]..A[i])
    // A[0] = B[0]
    // For i > 0: A[i] <= B[i], and if B[i] > B[i-1] then A[i] = B[i]
    // Max sum: A[i] = B[i] for all i
    // Min sum: A[0] = B[0]. For i > 0: if B[i] == B[i-1], A[i] = 0; if B[i] > B[i-1], A[i] = B[i]
    long long maxSum = 0, minSum = 0;
    for (int i = 0; i < n; i++) {
        maxSum += b[i];
        if (i == 0 || b[i] > b[i-1]) minSum += b[i];
        // else minSum += 0
    }
    cout << maxSum << "\n" << minSum << "\n";
    return 0;
}
