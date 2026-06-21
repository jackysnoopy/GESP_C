#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long s;
    cin >> N >> s;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    // Each mirror used once. Using mirror at b: position becomes 2b - pos.
    // To maximize final position, we want to use mirrors that push us right.
    // Key insight: the final position depends on the order.
    // If we use mirrors in order b1, b2, ..., bn:
    // p0 = s
    // p1 = 2*b1 - p0
    // p2 = 2*b2 - p1 = 2*b2 - 2*b1 + p0
    // pk = (-1)^k * s + 2 * sum_{i=1}^{k} (-1)^{k-i} * b_i
    // For n mirrors: pn = (-1)^n * s + 2 * sum_{i=1}^{n} (-1)^{n-i} * b_i
    // If n is even: pn = s + 2 * (b_n - b_{n-1} + b_{n-2} - ... + b_2 - b_1)
    //   Wait let me recompute:
    //   pn = s + 2*(-b1 + b2 - b3 + b4 - ... + bn) when n is even
    //   pn = -s + 2*(b1 - b2 + b3 - ... - bn) when n is odd
    // To maximize: for even n, maximize (-b1 + b2 - b3 + ... + bn)
    //   = (b2+b4+...+bn) - (b1+b3+...+b_{n-1})
    //   To maximize, put larger values in even positions.
    //   Sort A, assign largest to even positions.
    // For odd n, maximize (b1 - b2 + b3 - ... - bn) then subtract s.
    //   = (b1+b3+...+bn) - (b2+b4+...+b_{n-1})
    //   To maximize, put larger values in odd positions.
    //   Sort A, assign largest to odd positions.
    
    sort(A.begin(), A.end());
    long long result;
    if (N % 2 == 0) {
        // pn = s + 2*(sum_even - sum_odd)
        // Assign sorted: smallest to odd positions, largest to even
        long long sum_even = 0, sum_odd = 0;
        for (int i = 0; i < N; i++) {
            if ((i + 1) % 2 == 0) sum_even += A[i]; // even position (1-indexed)
            else sum_odd += A[i];
        }
        result = s + 2 * (sum_even - sum_odd);
    } else {
        // pn = -s + 2*(sum_odd - sum_even)
        // Assign sorted: largest to odd positions
        long long sum_even = 0, sum_odd = 0;
        for (int i = 0; i < N; i++) {
            if ((i + 1) % 2 == 0) sum_even += A[i];
            else sum_odd += A[i];
        }
        result = -s + 2 * (sum_odd - sum_even);
    }
    cout << result << endl;
    return 0;
}
