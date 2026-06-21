#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int N;
    cin >> N;
    vector<long long> C(N + 1);
    for (int i = 1; i <= N; i++) cin >> C[i];
    long long sumC = 0;
    for (int i = 1; i <= N; i++) sumC += C[i];
    auto gain = [&](int i) { return C[i] == 0 ? 1 : 0; };
    auto linearDP = [&](int lo, int hi) -> int {
        if (lo > hi) return 0;
        int prev2 = 0, prev1 = 0;
        for (int i = lo; i <= hi; i++) {
            int cur = max(prev1, prev2 + gain(i));
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    };
    int case1 = 0, case2 = 0;
    if (C[1] == 0) {
        case1 = 1 + linearDP(3, N - 1);
    }
    case2 = linearDP(2, N);
    int misGain = max(case1, case2);
    cout << sumC + misGain << "\n";
    return 0;
}
