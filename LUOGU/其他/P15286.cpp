#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m, k;
    cin >> n >> m >> k;
    // Each arrow: if offset p, score = max(0, n - p).
    // Total offset across m arrows = k.
    // To maximize total score: spread offset evenly to minimize loss.
    // If k <= n*m (each arrow can absorb some offset without going to 0):
    //   We want to minimize sum of losses = sum of min(p_i, n) where sum(p_i)=k.
    //   Since n-p_i for p_i < n, and 0 for p_i >= n.
    //   Loss per arrow = min(p_i, n). Total loss = sum of min(p_i, n).
    //   To minimize loss: spread offset as evenly as possible.
    //   Each arrow gets at most n offset (beyond that, wasted).
    //   Arrows that get >= n offset: 0 score, wasted offset.
    //   Remaining arrows share the rest evenly.
    //
    // Actually: total score = m*n - sum(min(p_i, n)).
    // To maximize score, minimize sum(min(p_i, n)).
    // Given sum(p_i) = k, minimize sum(min(p_i, n)).
    //
    // Each arrow: p_i >= 0, sum = k.
    // min(p_i, n) = p_i if p_i <= n, else n.
    // sum(min(p_i, n)) >= sum(p_i) only when all p_i <= n (then sum = k).
    // If some p_i > n, those contribute n instead of p_i, so sum(min) < k.
    //
    // Wait, that's wrong. min(p_i, n) <= p_i, so sum(min(p_i, n)) <= k.
    // To minimize sum(min(p_i, n)): we want as many arrows as possible to have p_i > n,
    // because those contribute only n instead of their full p_i.
    // But we want to MINIMIZE sum(min(p_i, n)).
    //
    // If we put all k on one arrow: sum(min) = min(k, n).
    // If we spread evenly: sum(min) = min(ceil(k/m)*m... no.
    //
    // Let's think differently. Score = sum(max(0, n - p_i)).
    // = m*n - sum(min(p_i, n)).
    // To maximize score: minimize sum(min(p_i, n)).
    //
    // For an arrow with p_i <= n: contributes p_i to sum(min).
    // For an arrow with p_i > n: contributes n to sum(min).
    //
    // Strategy: concentrate offset on as few arrows as possible.
    // Put k on one arrow: sum(min) = min(k, n). Score = m*n - min(k, n).
    // Spread across arrows: if all p_i <= n, sum(min) = k. Score = m*n - k.
    //
    // So concentrating is better when min(k, n) < k, i.e., k > n.
    // When k <= n: sum(min) = k regardless. Score = m*n - k.
    // When k > n: concentrating gives sum(min) = n. Score = m*n - n.
    //   Spreading gives sum(min) = k (if k <= m*n). Score = m*n - k < m*n - n.
    //   So concentrating is better!
    //
    // But wait: if k > n, we put k on one arrow, sum(min) = n.
    // Can we do better? Put n+1 on one arrow (sum(min)=n) and k-n-1 on another.
    // If k-n-1 > n: sum(min) = n + n = 2n. Worse!
    // So put ALL k on one arrow: sum(min) = min(k, n) = n.
    //
    // Actually wait. If k > n*m, then we must have some arrows with p_i = 0? No,
    // we just need sum(p_i) = k. We can put all k on one arrow.
    // sum(min) = min(k, n) = n. Score = m*n - n.
    //
    // If k <= n: sum(min) = k regardless of distribution. Score = m*n - k.
    //
    // But wait, is that right? k=5, n=3, m=2.
    // Put all 5 on one arrow: score = max(0,3-5) + max(0,3-0) = 0+3 = 3.
    // Put 2 and 3: score = max(0,3-2) + max(0,3-3) = 1+0 = 1.
    // Put 2.5 each: not integer, but 2,3 gives 1.
    // Optimal: 0,5 gives 3. 5,0 gives 3. Both give 3 = m*n - n = 6-3 = 3.
    // And m*n - k = 6 - 5 = 1. So the formula m*n - k is WRONG.
    
    // Let me redo. Score = sum(max(0, n - p_i)).
    // We want to maximize this. sum(p_i) = k, p_i >= 0.
    //
    // To maximize: make as many arrows as possible have small p_i.
    // Put all k on one arrow (or as few as possible).
    //
    // If we use c arrows (put offset on c arrows), each gets k/c (roughly).
    // Score = (m-c)*n + sum(max(0, n - p_i)) for the c arrows.
    //
    // To maximize: minimize c. c=1: put all k on one arrow.
    // Score = (m-1)*n + max(0, n - k).
    // = (m-1)*n + max(0, n-k).
    // If k <= n: = (m-1)*n + n - k = m*n - k.
    // If k > n: = (m-1)*n + 0 = (m-1)*n = m*n - n.
    
    // Is c=1 always optimal? What about c=0 (k=0)?
    // c=0 only if k=0. Score = m*n. Correct.
    
    // What about c=2? (m-2)*n + max(0, n-a) + max(0, n-b) where a+b=k.
    // = (m-2)*n + max(0, n-a) + max(0, n-b).
    // If a <= n and b <= n: = (m-2)*n + n-a + n-b = (m-2)*n + 2n - k = m*n - k.
    // Same as c=1 when k <= n!
    // If a > n: = (m-2)*n + 0 + max(0, n-b) <= (m-2)*n + n = (m-1)*n.
    // Same as c=1 when k > n.
    
    // So c=1 is always optimal (or equivalent).
    
    // Answer = (m-1)*n + max(0, n-k) = m*n - min(k, n).
    long long ans = m * n - min(k, n);
    cout << ans << endl;
    return 0;
}
