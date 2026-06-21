#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long x; cin >> x;
    // Divide x by p1^a1 * p2^a2 where p1, p2 are different primes.
    // We can do this any number of times. Minimize x.
    // Key: we can remove any p^a * q^b where p, q are different primes.
    // So we can remove any number with at least 2 distinct prime factors.
    // The remaining x must have 0 or 1 distinct prime factor.
    // If x has 0 distinct prime factors: x = 1. Already minimal.
    // If x has 1 distinct prime factor: x = p^k. We can't reduce further
    //   (any operation needs 2 different primes).
    // If x has 2+ distinct prime factors: we can reduce.
    //   Remove p1^a1 * p2^a2 to get x / (p1^a1 * p2^a2).
    //   We want to remove as much as possible.
    //   If x = p1^a1 * p2^a2 * ... * pk^ak with k >= 2:
    //   Remove p1^a1 * p2^a2 to get p3^a3 * ... * pk^ak.
    //   If k-1 >= 2: continue removing.
    //   If k-1 = 1: we're left with p3^a3. Can't reduce further.
    //   If k-1 = 0: we're left with 1.
    //   
    //   So the minimum is: if x has >= 2 distinct prime factors, we can reduce to
    //   the largest prime power factor. If x has <= 1 distinct prime factor, x is already minimal.
    //   
    //   Wait, we can choose which two primes to remove at each step.
    //   If x = p1^a1 * p2^a2 * ... * pk^ak:
    //   Step 1: remove p1^a1 * p2^a2. Left: p3^a3 * ... * pk^ak.
    //   If k >= 3: continue. Step 2: remove p3^a3 * p4^a4. Left: p5^a5 * ... * pk^ak.
    //   ...
    //   If k is even: left with 1.
    //   If k is odd: left with pk^ak.
    //   
    //   But we can also remove different amounts!
    //   For x = 2^3 * 3^2 * 5:
    //   Remove 2^3 * 3^2 = 72. Left: 5.
    //   Or remove 2^3 * 5 = 40. Left: 3^2 = 9.
    //   Or remove 3^2 * 5 = 45. Left: 2^3 = 8.
    //   Minimum: 5.
    //   
    //   For x = 2^3 * 3^2 * 5 * 7:
    //   Remove 2^3 * 3^2 = 72. Left: 5 * 7 = 35. Then remove 5*7=35. Left: 1.
    //   Or remove 2^3 * 5 = 40. Left: 3^2 * 7 = 63. Then remove 3^2*7=63. Left: 1.
    //   Always end at 1 if k >= 4 (even).
    //   
    //   For k = 3 (odd): end at the largest prime power.
    //   For k = 2: end at min(p1^a1, p2^a2).
    //   
    //   Wait, for k=2: x = p1^a1 * p2^a2. Remove p1^a1 * p2^a2. Left: 1.
    //   So minimum is 1!
    //   
    //   Hmm, but we can only remove p1^a1 * p2^a2 if a1, a2 are the FULL exponents.
    //   The operation: choose p1, a1, p2, a2. x must be divisible by p1^a1 * p2^a2.
    //   Then x = x / (p1^a1 * p2^a2).
    //   
    //   So for x = 2^3 * 3^2: remove 2^3 * 3^2 = 72. x = 1.
    //   For x = 2^3 * 3^2 * 5: remove 2^3 * 3^2 = 72. x = 5. Can't reduce (only 1 prime).
    //   Or remove 2^3 * 5 = 40. x = 9. Can't reduce.
    //   Or remove 3^2 * 5 = 45. x = 8. Can't reduce.
    //   Minimum: 5.
    //   
    //   For x = 2^3 * 3^2 * 5 * 7: remove 2^3 * 3^2 = 72. x = 35. Then remove 5*7=35. x=1.
    //   Minimum: 1.
    //   
    //   So the answer depends on the number of distinct prime factors:
    //   k = 0: x = 1. Answer = 1.
    //   k = 1: x = p^a. Answer = x.
    //   k = 2: x = p1^a1 * p2^a2. Answer = min(p1^a1, p2^a2).
    //   k >= 3: 
    //     If k is even: answer = 1.
    //     If k is odd: answer = min over all choices of which prime power to keep.
    //       We keep the smallest prime power. Answer = min(p_i^a_i).
    //   
    //   Wait, for k=3: x = p1^a1 * p2^a2 * p3^a3.
    //   Remove p1^a1 * p2^a2. Left: p3^a3.
    //   Or remove p1^a1 * p3^a3. Left: p2^a2.
    //   Or remove p2^a2 * p3^a3. Left: p1^a1.
    //   Minimum: min(p1^a1, p2^a2, p3^a3).
    //   
    //   For k=4: x = p1^a1 * p2^a2 * p3^a3 * p4^a4.
    //   Remove p1^a1 * p2^a2. Left: p3^a3 * p4^a4. Then remove p3^a3 * p4^a4. Left: 1.
    //   Answer: 1.
    //   
    //   So:
    //   k = 0: answer = 1.
    //   k = 1: answer = x.
    //   k >= 2 and even: answer = 1.
    //   k >= 3 and odd: answer = min(p_i^a_i).
    //   k = 2: answer = min(p1^a1, p2^a2).
    //   
    //   Wait, k=2 is even. So answer = 1 for k=2? Let me recheck.
    //   x = p1^a1 * p2^a2. Remove p1^a1 * p2^a2. x = 1. Yes, answer = 1!
    //   
    //   So: k = 0 or k >= 2 (even): answer = 1.
    //   k = 1: answer = x.
    //   k >= 3 (odd): answer = min(p_i^a_i).
    
    if (x == 1) { cout << 1 << "\n"; return 0; }
    vector<pair<long long,int>> factors;
    long long temp = x;
    for (long long p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            int cnt = 0;
            while (temp % p == 0) { temp /= p; cnt++; }
            factors.push_back({p, cnt});
        }
    }
    if (temp > 1) factors.push_back({temp, 1});
    int k = factors.size();
    if (k == 1) { cout << x << "\n"; return 0; }
    if (k % 2 == 0) { cout << 1 << "\n"; return 0; }
    // k is odd and >= 3
    long long ans = x;
    for (auto& f : factors) {
        long long pw = 1;
        for (int i = 0; i < f.second; i++) pw *= f.first;
        if (pw < ans) ans = pw;
    }
    cout << ans << "\n";
    return 0;
}
