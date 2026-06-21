#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    vector<int> V(N);
    for (int i = 0; i < N; i++) scanf("%d", &V[i]);
    sort(V.begin(), V.end());
    int keep = N - K;
    if (keep <= 1) { printf("0\n"); return 0; }
    vector<long long> d(N - 1);
    for (int i = 0; i < N - 1; i++) d[i] = (long long)V[i + 1] - V[i];
    int winDiffs = keep - 1;
    deque<int> dq;
    long long best = LLONG_MAX;
    for (int i = 0; i < N - 1; i++) {
        while (!dq.empty() && dq.front() <= i - winDiffs) dq.pop_front();
        while (!dq.empty() && d[dq.back()] >= d[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= winDiffs - 1) {
            int l = i - winDiffs + 1, r = i + 1;
            long long M = (long long)V[r] - V[l];
            long long m = d[dq.front()];
            best = min(best, M + m);
        }
    }
    printf("%lld\n", best);
    return 0;
}
