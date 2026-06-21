#include <iostream>
using namespace std;
const long long MOD = 1000000007;
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n; cin >> n;
    // Length n binary string, represents number C in [0, 2^n - 1].
    // For C > 1: P = max(A xor B) where A+B=C, A>0, B>0.
    // Q = min(A xor B) where A+B=C, A>0, B>0.
    // XOR power = P - Q.
    // Find max XOR power over all C in [1, 2^n - 1].
    //
    // For A+B=C: B = C-A. A xor B = A xor (C-A).
    // P = max over A in [1,C-1] of A xor (C-A).
    // Q = min over A in [1,C-1] of A xor (C-A).
    //
    // Key insight: A xor (C-A) depends on the bit pattern of C.
    // For C with all bits set (C = 2^n - 1): A xor (C-A) = A xor (~A) = C (all bits set).
    //   So P = C. And Q = ? For A=1: 1 xor (C-1) = 1 xor (2^n-2).
    //   For n=3, C=7: A=1, B=6, 1^6=5. A=2, B=5, 2^5=7. A=3, B=4, 3^4=7.
    //   P=7, Q=5. XOR power = 2.
    //
    // For C = 2^n - 2 (all bits except LSB): C=6 for n=3.
    //   A=1, B=5, 1^5=4. A=2, B=4, 2^4=6. A=3, B=3, 3^3=0. A=4, B=2, 4^2=6. A=5, B=1, 5^1=4.
    //   P=6, Q=0. XOR power = 6.
    //
    // For C = 2^n - 1 = 7: P=7, Q=5. Power=2.
    // For C = 6: P=6, Q=0. Power=6.
    // For C = 5: A=1,B=4,1^4=5. A=2,B=3,2^3=1. A=3,B=2,3^2=1. A=4,B=1,4^1=5.
    //   P=5, Q=1. Power=4.
    // For C = 4: A=1,B=3,1^3=2. A=2,B=2,2^2=0. A=3,B=1,3^1=2.
    //   P=2, Q=0. Power=2.
    // For C = 3: A=1,B=2,1^2=3. A=2,B=1,2^1=3.
    //   P=3, Q=3. Power=0.
    // For C = 2: A=1,B=1,1^1=0.
    //   P=0, Q=0. Power=0.
    //
    // For n=3: max power is 6 (from C=6).
    // The sample says answer is 6. Correct!
    //
    // So for general n, the maximum power comes from C = 2^n - 2.
    // For C = 2^n - 2: binary is 111...110.
    // P = C = 2^n - 2 (achieved when A = 2^(n-1), B = 2^(n-1) - 2).
    //   A xor B = 2^(n-1) xor (2^(n-1)-2).
    //   For n=3: A=4, B=2, 4^2=6. Yes, P=6.
    // Q = 0 (achieved when A = B = C/2 = 2^(n-1) - 1).
    //   A xor B = (2^(n-1)-1) xor (2^(n-1)-1) = 0.
    //   For n=3: A=3, B=3, 3^3=0. Yes, Q=0.
    // Power = P - Q = 2^n - 2 - 0 = 2^n - 2.
    //
    // Wait, for n=3: power = 6 = 2^3 - 2. Correct!
    // For n=2: C=2 (binary 10). P=0, Q=0. Power=0. But 2^2-2=2. Hmm.
    // Let me recheck: for n=2, C ranges from 1 to 3.
    // C=2: A=1,B=1,1^1=0. P=0,Q=0. Power=0.
    // C=3: A=1,B=2,1^2=3. A=2,B=1,2^1=3. P=3,Q=3. Power=0.
    // So for n=2, max power = 0.
    //
    // But 2^2-2 = 2. So the formula isn't 2^n - 2.
    //
    // Let me reconsider. For C = 2^n - 2:
    // Binary: 111...110 (n-1 ones followed by a zero).
    // P: max A xor B for A+B=C, A>0, B>0.
    //   A xor B = A xor (C-A). We want to maximize this.
    //   For A = 2^(n-1): B = C - 2^(n-1) = 2^(n-1) - 2.
    //   A xor B = 2^(n-1) xor (2^(n-1)-2).
    //   2^(n-1) in binary: 100...0 (n bits).
    //   2^(n-1)-2 in binary: 011...110 (n-2 ones and a zero).
    //   XOR: 111...110 = C. So P = C = 2^n - 2.
    //   Wait, but A xor B = C means A + B = C and A xor B = C. This happens when A & B = 0.
    //   A = 2^(n-1), B = 2^(n-1)-2. A & B = 2^(n-1) & (2^(n-1)-2) = 0. Yes!
    //
    // Q: min A xor B for A+B=C, A>0, B>0.
    //   A xor B = A xor (C-A). We want to minimize this.
    //   For A = C/2 = 2^(n-1)-1 (when C is even): B = C/2 = 2^(n-1)-1.
    //   A xor B = 0. So Q = 0.
    //   But wait, for n=2, C=2: A=B=1. 1^1=0. Q=0. P=0. Power=0.
    //   For n=2, C=2: P should be 0? Let me check all A:
    //   A=1: 1^1=0. That's the only option (A=1, B=1).
    //   So P=0, Q=0. Power=0.
    //   
    //   But I claimed P = C = 2^n - 2 = 2 for n=2. That's wrong!
    //   The issue: for n=2, C=2, A=2^(n-1)=2, B=C-A=0. But B must be > 0!
    //   So A=2 is not valid.
    //   
    //   For n=3, C=6: A=4, B=2. Both > 0. Valid.
    //   For n=2, C=2: A=2, B=0. B=0 not valid. So A=2 is not an option.
    //   
    //   So the formula P = C only works when A = 2^(n-1) and B = 2^(n-1)-2 are both > 0.
    //   B = 2^(n-1)-2 > 0 requires n >= 3.
    //   
    //   For n=2: max power = 0.
    //   For n=3: max power = 6.
    //   For n=4: C=14. A=8, B=6. 8^6=14. Q=0 (A=B=7). Power=14.
    //   So for n>=3: max power = 2^n - 2.
    //   For n=2: max power = 0.
    //   
    //   Wait, but the problem says n >= 2. And for n=2, the answer should be 0.
    //   Let me check: the problem asks for the maximum XOR power over all length-n binary strings.
    //   For n=2: strings are 00, 01, 10, 11. C = 0, 1, 2, 3.
    //   C=0: not > 1. C=1: not > 1. C=2: power=0. C=3: power=0.
    //   Max = 0.
    //   
    //   For n=3: strings 000 to 111. C = 0 to 7.
    //   C=6: power=6. Max = 6.
    //   
    //   So for n >= 3: answer = 2^n - 2. For n = 2: answer = 0.
    //   
    //   Wait, but is C = 2^n - 2 always the best?
    //   For n=4: C=14 gives power 14. What about C=13?
    //   C=13 (1101): A xor B for A+B=13.
    //   A=8, B=5: 8^5=13. A=4, B=9: 4^9=13. A=2, B=11: 2^11=9. A=1, B=12: 1^12=13.
    //   P=13. Q: A=6, B=7: 6^7=1. A=5, B=8: 5^8=13. Min is 1.
    //   Power = 13-1 = 12. Less than 14.
    //   
    //   C=12 (1100): A=8, B=4: 8^4=12. A=6, B=6: 6^6=0.
    //   P=12, Q=0. Power=12. Less than 14.
    //   
    //   C=10 (1010): A=8, B=2: 8^2=10. A=5, B=5: 5^5=0.
    //   P=10, Q=0. Power=10.
    //   
    //   So C=2^n-2 gives the maximum power = 2^n-2 for n>=3.
    //   
    //   Actually, I should double-check: is there any C with power > 2^n-2?
    //   P <= C (since A xor B <= A+B = C). Q >= 0. So power = P-Q <= C.
    //   For C <= 2^n-1, power <= 2^n-1.
    //   But for C = 2^n-1: P = 2^n-1, Q = 2^(n-1)-1 (for n>=2).
    //   Power = 2^n-1 - (2^(n-1)-1) = 2^(n-1).
    //   For n=3: 2^2 = 4 < 6. So C=7 gives power 4, less than C=6's power 6.
    //   For n=4: C=15: P=15, Q=7. Power=8 < 14.
    //   
    //   So the maximum is indeed 2^n-2 for n>=3.
    
    if (n == 2) {
        cout << 0 << "\n";
    } else {
        cout << (power(2, n, MOD) - 2 + MOD) % MOD << "\n";
    }
    return 0;
}
