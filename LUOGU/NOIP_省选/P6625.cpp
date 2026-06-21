#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // merge leftmost consecutive, replace with sum, insert at left
    // total score = sum of all prefix sums of the operations
    // Actually: optimal is to try all possible split points
    // score = sum of all prefix sums when processing left to right
    // The total score for sequence a[0..n-1] is:
    // For each merge of a[l..r], the score increases by sum(a[l..r])
    // We want to maximize total score, we can stop anytime
    // Key insight: total = sum over all positions of (n-i)*a[i] for some arrangement
    // Actually the score equals sum of prefix sums of prefix sums...
    // Let's think differently: after all merges, we get total = sum of all partial sums
    // For a sequence, the score from merging everything = sum_{i=0}^{n-1} (i+1)*a[i] (if sorted by original order)
    // Wait no. Let me re-think.
    // Operation: take leftmost k>=2 cards, replace with their sum at left.
    // Score += sum of those k cards.
    // Final: sequence has 1 card.
    // Let s = total sum. Then score = s + sum of partial sums during merging.
    // Actually total score = sum of all intermediate sums.
    // If we merge everything: score = a[0]+a[1] + (a[0]+a[1])+a[2] + ... 
    // = sum_{i=1}^{n-1} sum_{j=0}^{i} a[j] = sum_{j=0}^{n-1} a[j]*(n-j)
    // We can stop anytime. So max score = max over all prefixes of the full merge score? No.
    // We can choose how to merge. Best: merge all at once if positive sum.
    // Actually we can also choose to stop after some merges.
    // Key: total score for full merge = sum_{j} a[j]*(n-j)
    // For any prefix of length k: score = sum_{j=0}^{k-1} a[j]*(k-j)
    // We want max over k of sum_{j=0}^{k-1} a[j]*(k-j)
    // = sum_{j=0}^{k-1} a[j]*k - sum_{j=0}^{k-1} a[j]*j
    // = k*prefix[k] - weighted_prefix[k]
    long long ans = 0;
    long long ps = 0, wps = 0;
    for (int i = 0; i < n; i++) {
        ps += a[i];
        wps += (long long)a[i] * i;
        long long cur = (long long)(i + 1) * ps - wps;
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
