#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> f(n);
    for (int i = 0; i < n; i++) cin >> f[i];
    
    if (n == 1) {
        cout << "simple" << endl;
        cout << 1 << endl;
        cout << 0 << " " << f[0] << endl;
        return 0;
    }
    
    // For degree n-1 polynomial, we need n-1 factors.
    // The leading coeff is sum of all a_i = f[n-1].
    // The constant is sum of all b_i = f[0].
    // 
    // For the tensor product of linear functions,
    // the result has a specific structure. Let me think about it.
    //
    // Actually, for 2 factors (degree 2):
    // (a1*x+b1) ⊗ (a2*x+b2) = (b1+b2) + max(b1+a2,a1+b2)*x + (a1+a2)*x^2
    // So: f[0]=b1+b2, f[1]=max(b1+a2,a1+b2), f[2]=a1+a2
    // WLOG a1+b2 >= b1+a2, then f[1]=a1+b2
    // f[1] = a1+b2 >= (a1+a2+b1+b2)/2 = (f[0]+f[2])/2
    // So f[1] >= (f[0]+f[2])/2 is necessary.
    // Also f[1] <= f[0]+f[2] (since max of two things each <= f[0]+f[2]).
    //
    // For 3 factors: more complex. The result depends on the order.
    //
    // Let me try a different approach: greedy construction.
    // Start with the highest degree term. Each factor contributes 1 to the degree.
    // The leading coeff of the product is sum of all a_i.
    //
    // For k factors, the j-th coefficient (0-indexed) is:
    // f[j] = max over all ways to distribute j "x contributions" among k factors
    //        of (sum of a_i for factors contributing x + sum of b_i for others)
    //
    // This is equivalent to: f[j] = max over all subsets S of {1..k} with |S|=j
    //        of (sum_{i in S} a_i + sum_{i not in S} b_i)
    //     = max over all S with |S|=j of (sum_S a_i + sum_{not S} b_i)
    //     = max over all S with |S|=j of (sum_S (a_i - b_i) + sum_all b_i)
    //     = sum_all b_i + max over all S with |S|=j of sum_S (a_i - b_i)
    //
    // Let d_i = a_i - b_i. Then:
    // f[j] = sum_b + max sum of j values from {d_1, ..., d_k}
    //
    // To maximize sum of j values from d: sort d descending, take top j.
    // So f[j] = sum_b + sum of top j d_i values.
    //
    // Let's verify for k=2 (degree 2):
    // d_1 = a1-b1, d_2 = a2-b2. sum_b = b1+b2.
    // f[0] = sum_b + 0 = b1+b2. ✓
    // f[1] = sum_b + max(d_1, d_2) = b1+b2 + max(a1-b1, a2-b2)
    //        = max(a1+b2, a2+b1). ✓
    // f[2] = sum_b + d_1+d_2 = b1+b2 + a1-b1+a2-b2 = a1+a2. ✓
    //
    // So the formula is:
    // f[j] = B + sum of top j values of {d_i}
    // where B = sum_b, d_i = a_i - b_i.
    //
    // Let s_j = sum of top j d values (sorted descending).
    // f[j] = B + s_j.
    // So s_j = f[j] - B.
    //
    // s_0 = 0, s_k = sum of all d_i = sum_a - sum_b = f[k-1] - f[0]... wait.
    // sum_a = f[k-1] (leading coeff). sum_b = f[0] (constant).
    // s_k = sum_a - sum_b = f[k-1] - f[0].
    //
    // Also s_j = f[j] - B = f[j] - f[0].
    //
    // The d values sorted descending: d[1] >= d[2] >= ... >= d[k].
    // s_j = d[1] + ... + d[j].
    // s_j - s_{j-1} = d[j] >= 0 (for j <= number of positive d values).
    // Actually d[j] can be negative.
    //
    // The condition for the polynomial to be simple:
    // 1. s_j = f[j] - f[0] for all j.
    // 2. The sequence s_0, s_1, ..., s_k has the property that
    //    d_j = s_j - s_{j-1} are non-increasing (since d is sorted descending).
    //    i.e., s_j - s_{j-1} >= s_{j+1} - s_j, i.e., 2*s_j >= s_{j-1} + s_{j+1}.
    //    This means s is concave (second differences <= 0).
    //
    // So the condition is: f[j] - f[0] forms a concave sequence.
    // i.e., f[j] - f[0] is concave in j.
    // Equivalently: f[j+1] + f[j-1] <= 2*f[j] for all j from 1 to k-1.
    //
    // Wait, let me check: d_j = s_j - s_{j-1} = f[j] - f[j-1].
    // d is non-increasing: d_j >= d_{j+1}, i.e., f[j]-f[j-1] >= f[j+1]-f[j].
    // i.e., 2*f[j] >= f[j-1] + f[j+1]. This means f is concave.
    //
    // Let me verify for the sample:
    // f = [2, 3, 3]. f is concave? 2*3 >= 2+3 = 5. 6 >= 5. ✓
    // f = [97, 109, 101]. 2*109 >= 97+101 = 198. 218 >= 198. ✓
    // f = [9,9,8,2,4,4,3,5,3]. 
    //   j=1: 2*9 >= 9+8 = 17. 18 >= 17. ✓
    //   j=2: 2*8 >= 9+2 = 11. 16 >= 11. ✓
    //   j=3: 2*2 >= 8+4 = 12. 4 >= 12. ✗
    //   So not concave. Output "nice". ✓
    //
    // So the condition is: f[0..n-1] must be concave (2*f[j] >= f[j-1]+f[j+1]).
    // And f must be simple means it IS concave.
    //
    // Wait, but we also need d values to be integers (since a_i, b_i are integers).
    // And we need to find actual a_i, b_i values.
    //
    // The construction:
    // d_j = f[j] - f[j-1] for j=1..k (these are the d values in sorted order)
    // B = f[0] (sum of b_i)
    // We need sum of d_i = f[k] - f[0] (sum of a_i - sum of b_i)
    // And sum of b_i = f[0].
    //
    // The d values are d_1 >= d_2 >= ... >= d_k (non-increasing).
    // We need to find a_i, b_i such that:
    // - a_i - b_i = d_i (in sorted order)
    // - sum b_i = f[0]
    // - sum a_i = f[k]
    //
    // sum a_i = sum (d_i + b_i) = sum d_i + sum b_i = (f[k]-f[0]) + f[0] = f[k]. ✓
    //
    // So we just need b_i >= 0 (or b_i can be any integer?) and a_i >= 0.
    // The problem says a, b are integers (整数), so they can be negative.
    // But let me check: the problem says "Mivik 函数为能表示为 f(x)=ax+b 形式的函数，其中 a、b 均为整数"
    // So a, b are integers (can be negative).
    //
    // So we can choose any b_i values that sum to f[0], and set a_i = b_i + d_i.
    // Simplest: set b_1 = f[0], b_2 = ... = b_k = 0.
    // Then a_1 = f[0] + d_1, a_i = d_i for i > 1.
    //
    // Wait, but we need to output the factors in order. The tensor product is left-associative.
    // The order of factors matters!
    //
    // Actually, re-reading the problem: "Mivik 卷积是左结合的"
    // And the formula for f[j] depends on the sorted d values, not the order.
    // So the order of factors doesn't matter for the result!
    //
    // Hmm wait, that can't be right. Let me check with 3 factors.
    // (a1*x+b1) ⊗ (a2*x+b2) ⊗ (a3*x+b3)
    // = ((a1*x+b1) ⊗ (a2*x+b2)) ⊗ (a3*x+b3)
    //
    // First: (a1*x+b1) ⊗ (a2*x+b2) = c0 + c1*x + c2*x^2
    // where c0 = b1+b2, c1 = max(b1+a2,a1+b2), c2 = a1+a2.
    //
    // Then: (c0+c1*x+c2*x^2) ⊗ (a3*x+b3) = d0 + d1*x + d2*x^2 + d3*x^3
    // d0 = c0+b3 = b1+b2+b3
    // d1 = max(c0+a3, c1+b3) = max(b1+b2+a3, max(b1+a2,a1+b2)+b3)
    //     = max(b1+b2+a3, b1+a2+b3, a1+b2+b3)
    // d2 = max(c1+a3, c2+b3) = max(max(b1+a2,a1+b2)+a3, a1+a2+b3)
    //     = max(b1+a2+a3, a1+b2+a3, a1+a2+b3)
    // d3 = c2+a3 = a1+a2+a3
    //
    // So d_j = max over all subsets S of {1,2,3} with |S|=j of sum_{i in S} a_i + sum_{i not in S} b_i.
    // This confirms the formula! The order doesn't matter.
    //
    // So the algorithm is:
    // 1. Check if f is concave: 2*f[j] >= f[j-1]+f[j+1] for all j.
    // 2. If yes, construct the factors.
    // 3. If no, output "nice".
    //
    // For construction:
    // d_j = f[j] - f[j-1] for j=1..k (k = n-1)
    // B = f[0]
    // Choose b_1 = B, b_2 = ... = b_k = 0.
    // a_1 = b_1 + d_1 = f[0] + f[1] - f[0] = f[1]
    // a_j = b_j + d_j = d_j = f[j] - f[j-1] for j > 1.
    //
    // Wait, but d is sorted descending. The d values I computed are f[j]-f[j-1],
    // which should be non-increasing if f is concave. So they are already sorted.
    //
    // Output: k factors, each (a_i, b_i).
    // Factor 1: (f[1], f[0])
    // Factor j (j>1): (f[j]-f[j-1], 0)
    //
    // Let me verify for sample 1: f = [2, 3, 3]. k = 2.
    // d = [3-2, 3-3] = [1, 0]. B = 2.
    // Factor 1: (3, 2). Factor 2: (1, 0).
    // Check: (3x+2) ⊗ (x+0) = (2+0) + max(2+1, 3+0)*x + (3+1)*x^2
    //   = 2 + 3*x + 4*x^2. But f = [2, 3, 3]. ✗
    //
    // The issue: my construction is wrong. Let me reconsider.
    //
    // The d values are the a_i - b_i values, sorted descending.
    // d_1 >= d_2 >= ... >= d_k.
    // s_j = sum of top j d values.
    // f[j] = B + s_j.
    //
    // For f = [2, 3, 3]: B = 2. s_1 = 1, s_2 = 1.
    // d values: d_1 = s_1 = 1, d_2 = s_2 - s_1 = 0.
    // So d = [1, 0]. a_1 - b_1 = 1, a_2 - b_2 = 0.
    // sum b = 2. sum a = sum d + sum b = 1 + 2 = 3 = f[2]. ✓
    //
    // Choose b_1 = 2, b_2 = 0. Then a_1 = 3, a_2 = 0.
    // (3x+2) ⊗ (0*x+0) = (2+0) + max(2+0, 3+0)*x + (3+0)*x^2
    //   = 2 + 3x + 3x^2. ✓✓✓
    //
    // But wait, (0*x+0) is a valid Mivik function? The problem says a,b are integers.
    // And the problem says f(x) = ax+b. So a=0, b=0 gives f(x)=0. That's valid.
    //
    // But the expected output is:
    // simple
    // 2
    // 2 1
    // 1 1
    // Let me check: (2x+1) ⊗ (x+1) = (1+1) + max(1+1, 2+1)*x + (2+1)*x^2
    //   = 2 + 3x + 3x^2. ✓
    //
    // So there are multiple valid constructions. My construction also works.
    //
    // But wait, I need to check: is the condition "f is concave" sufficient?
    // Let me check sample 2: f = [97, 109, 101]. 
    // 2*109 = 218 >= 97+101 = 198. ✓
    // d = [109-97, 101-109] = [12, -8]. B = 97.
    // Factor 1: (109, 97). Factor 2: (-8, 0).
    // (109x+97) ⊗ (-8x+0) = (97+0) + max(97+(-8), 109+0)*x + (109+(-8))*x^2
    //   = 97 + 109x + 101x^2. ✓
    //
    // Expected output: simple, 2 factors: (54,42) and (47,55).
    // (54x+42) ⊗ (47x+55) = (42+55) + max(42+47, 54+55)*x + (54+47)*x^2
    //   = 97 + 109x + 101x^2. ✓
    //
    // Great, my approach works. But I need to verify the concavity condition
    // is both necessary and sufficient.
    //
    // Necessary: we showed f[j]-f[j-1] must be non-increasing.
    // Sufficient: if f is concave, we can construct the factors as above.
    //
    // But wait, I also need to handle the case where d values might not be integers?
    // No, d_j = f[j] - f[j-1], and f values are integers, so d values are integers.
    // And b values are integers. So a values are integers. ✓
    //
    // Also, I need to handle n=1 (degree 0): just a constant. Output (0, f[0]).
    
    if (n == 1) {
        cout << "simple" << endl;
        cout << 1 << endl;
        cout << 0 << " " << f[0] << endl;
        return 0;
    }
    
    // Check concavity: 2*f[j] >= f[j-1] + f[j+1]
    for (int j = 1; j < n - 1; j++) {
        if (2 * f[j] < f[j-1] + f[j+1]) {
            cout << "nice" << endl;
            return 0;
        }
    }
    
    int k = n - 1;
    cout << "simple" << endl;
    cout << k << endl;
    // Factor 1: (f[1], f[0])
    cout << f[1] << " " << f[0] << endl;
    // Factor j (j=2..k): (f[j]-f[j-1], 0)
    for (int j = 2; j < n; j++) {
        cout << f[j] - f[j-1] << " " << 0 << endl;
    }
    
    return 0;
}
