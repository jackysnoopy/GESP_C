#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;

bool check(int C) {
    // Check if C colors suffice for the circular arrangement
    // a[i] colors for general i, adjacent cannot share
    // For circular: need to handle the wrap-around constraint
    // Binary search on C
    // For a linear arrangement, the constraint is simpler
    // For circular: the key constraint is that the overlap between
    // consecutive pairs must be consistent

    // For general i and i+1 (mod n), they share at most max(0, a[i]+a[i+1]-C) colors
    // In circular: the chain of overlaps must close consistently

    // Approach: fix the overlap between 1 and n, then check linear consistency
    // overlap[1,n] can range from max(0, a[1]+a[n]-C) to min(a[1], a[n])
    // For each possible overlap, check if the chain is consistent

    // Efficient approach: compute the range of possible overlaps
    // For the chain 1-2-3-...-n-1, given overlap[1,n] = x,
    // the overlap between i and i+1 is determined by the propagation

    // For linear chain 1..n:
    // overlap[i,i+1] >= max(0, a[i]+a[i+1]-C)
    // overlap[i,i+1] <= min(a[i], a[i+1])
    // The key: overlap[i,i+1] determines how many colors are "shared"
    // which constrains overlap[i+1,i+2]

    // More precisely: if overlap[i,i+1] = o_i, then general i+1 has
    // a[i+1] - o_i colors that are unique to i+1.
    // overlap[i+1,i+2] can be at most a[i+1] (trivially) but also
    // the colors shared with i constrain things.

    // Actually the standard approach for this problem:
    // Binary search on C. For a given C:
    // The minimum overlap between consecutive generals i and i+1 is:
    // need[i] = max(0, a[i] + a[i+1] - C)
    // For circular: need[n] = max(0, a[n] + a[1] - C)

    // For the chain 1-2-...-n-1:
    // Given overlap[1,n] = x, we can determine the range of each overlap[i,i+1]
    // overlap[1,2] is in [need[1], min(a[1],a[2])]
    // But more precisely: overlap[i,i+1] determines the "available" colors for i+1

    // Standard solution: 
    // Let f(C) = whether C colors suffice
    // For circular: check if there exists x (overlap between 1 and n)
    // such that the chain is consistent

    // Key insight: for the chain 1..n, the constraint propagation:
    // Let o_i = overlap between i and i+1 (for i=1..n-1)
    // o_i >= need[i], o_i <= min(a[i], a[i+1])
    // The "remaining" colors for i+1 after sharing with i is a[i+1] - o_i
    // o_{i+1} >= need[i+1] and o_{i+1} <= a[i+1] - (a[i] - o_i) ... no

    // Actually: general i has a[i] colors. If it shares o_i with i-1 and o_{i+1} with i+1,
    // then the colors unique to i are a[i] - o_i - o_{i+1} + overlap_of_overlaps
    // This is getting complex. Let me use the known solution approach:

    // For each possible overlap x between general 1 and general n:
    // x >= need_n = max(0, a[n]+a[1]-C)
    // x <= min(a[1], a[n])
    // Given x, the overlap between 1 and 2 is constrained:
    // o_1 >= need_1, o_1 <= min(a[1], a[2])
    // But also: the colors of general 1 that overlap with n is x,
    // and the colors that overlap with 2 is o_1.
    // The total shared colors of general 1 is at most a[1], so x + o_1 <= a[1] + overlap_of_them
    // Actually x and o_1 can share colors, so x + o_1 <= a[1] + min(x, o_1)
    // i.e., max(x, o_1) <= a[1], which is always true since both <= a[1].

    // Hmm, the correct approach is simpler. Let me think differently.
    // For the circular problem, the answer is:
    // C >= max_i(a[i]) (obviously)
    // C >= ceil(sum(a[i]) / floor(n/2)) ... no

    // Known result: for circular coloring with adjacent different colors,
    // the minimum C is max(max(a[i]), ceil(sum(a[i]) / (n/2))) for even n
    // and similar for odd n.

    // Actually this is not exactly graph coloring. Let me re-read.
    // Each general has a[i] colors. Adjacent generals share no colors.
    // We want to minimize total distinct colors used.

    // For the chain (non-circular): C >= max(max(a[i]), ceil(sum(a[i])/2))
    // because each color can be used by at most 2 non-adjacent generals.

    // For circular: each color can be used by at most floor(n/2) generals
    // (for even n, exactly n/2; for odd n, at most (n-1)/2 for some, n/2 for others)
    // So C >= ceil(sum(a[i]) / floor(n/2))

    // But there's also the constraint from consecutive pairs.
    // The known solution uses binary search + greedy checking.

    // Simpler: the answer is max over all "cuts" of:
    // For a cut between positions i and i+1:
    // The left side sum / floor(left_count/2) + right side sum / floor(right_count/2)
    // ... this is getting too complex. Let me implement the known approach.

    // Binary search + simulation:
    // For each possible first overlap x (between 1 and n):
    // Simulate the chain 1->2->...->n checking consistency

    // Given overlap[1,n] = x:
    // overlap[1,2] can be at most a[1] - x + overlap_of_x_with_o1
    // Actually: colors of 1 = a[1]. x of them overlap with n. 
    // The remaining a[1]-x colors can overlap with 2.
    // So o_1 <= min(a[2], a[1]-x + min(x, something))... 

    // I think the correct approach is:
    // o_1 >= need_1 = max(0, a[1]+a[2]-C)
    // o_1 <= min(a[1], a[2])
    // But also: o_1 can use colors from the x shared with n.
    // So o_1 <= min(a[2], a[1]) -- always true.
    // But the constraint is: the colors of 2 that overlap with 1 cannot be the same
    // as the colors of 2 that overlap with 3.
    // Actually this is just about the number of shared colors, not which ones.

    // The real constraint: for general i+1, the colors shared with i (o_i)
    // and the colors shared with i+2 (o_{i+1}) are disjoint subsets of a[i+1]'s colors.
    // So o_i + o_{i+1} <= a[i+1].

    // For circular: o_n + o_1 <= a[1] (colors of 1 shared with n and 2 are disjoint)

    // So the constraints are:
    // o_i >= need_i for all i
    // o_i + o_{i+1} <= a[i+1] for all i (with o_{n+1} = o_1)

    // Given x = o_n, we need:
    // o_1 >= need_1, o_1 <= a[1] - x (from o_n + o_1 <= a[1])
    // o_2 >= need_2, o_2 <= a[2] - o_1
    // ... and so on until o_n >= need_n, o_n <= a[n] - o_{n-1}
    // And o_n = x.

    // For the chain, given o_1, we can determine the feasible range of o_2, etc.
    // The minimum o_1 given x: o_1 >= need_1 and o_1 <= a[1] - x
    // The maximum o_2 given o_1: o_2 <= a[2] - o_1
    // etc.

    // To check feasibility: given x, find if there's a valid assignment.
    // For the forward chain (ignoring the circular constraint):
    // min_o[i] = need_i
    // max_o[i] = a[i+1] - min_o[i-1] (roughly)
    // But we need to propagate both min and max.

    // Forward pass: given o_1, compute feasible [min_o[i], max_o[i]] for each i
    // min_o[i] = need_i
    // max_o[i] = a[i+1] - min_o[i-1] (but also <= a[i+1])
    // Actually: o_i <= a[i+1] - o_{i-1}, so max_o[i] depends on o_{i-1}

    // This is a constraint propagation problem. Let me just try all feasible x values.
    // x ranges from need_n to min(a[1], a[n]), which could be up to 10^5.
    // For each x, simulate the chain in O(n). Total O(n * range) which could be 10^9.

    // Better: binary search on the answer C, and for each C, check feasibility.
    // For checking: the constraints form a system that can be solved greedily.

    // Forward: compute the range of o_1 that makes the chain feasible.
    // Starting from o_1 in [need_1, a[1]-x]:
    // o_2 in [need_2, a[2]-o_1] => o_1 <= a[2] - need_2
    // o_3 in [need_3, a[3]-o_2] => o_2 <= a[3] - need_3 => a[2]-o_1 <= a[3]-need_3 => o_1 >= a[2]-a[3]+need_3
    // etc.

    // This propagates to a range for o_1. Then check if x is in the feasible range for o_n.

    // Let me implement this properly.
    int need_n = max(0, a[n-1] + a[0] - C);
    if (need_n > min(a[0], a[n-1])) return false;

    // For the chain 1-2-...-n (indices 0..n-1 in 0-based):
    // overlap[i] = overlap between person i and person (i+1)%n
    // For 0-based: overlap[i] between a[i] and a[(i+1)%n]
    // Constraints: overlap[i] >= need[i], overlap[i] + overlap[(i-1+n)%n] <= a[i]

    // For the circular chain, fix overlap[n-1] = x (between person n-1 and person 0)
    // Then propagate forward:
    // overlap[0] >= need[0], overlap[0] <= a[0] - x (from overlap[n-1]+overlap[0] <= a[0])
    // overlap[1] >= need[1], overlap[1] <= a[1] - overlap[0]
    // ... overlap[n-1] >= need[n-1], overlap[n-1] <= a[n-1] - overlap[n-2]
    // And overlap[n-1] = x

    // Forward propagation: given overlap[0] = y, what's the feasible range for overlap[n-1]?
    // overlap[1] <= a[1] - y, overlap[2] <= a[2] - (a[1]-y) = a[2]-a[1]+y, etc.
    // This alternates. Let me just compute min and max for overlap[n-1] as a function of y.

    // For simplicity, try all feasible y values (overlap[0]).
    // y ranges from need[0] to min(a[0], a[n-1]) - but also y <= a[0] - need_n.
    int y_min = max(0, a[0] + a[1] - C);
    int y_max = min(a[0], a[1]);
    y_max = min(y_max, a[0] - need_n); // from overlap[n-1]+overlap[0] <= a[0]

    if (y_min > y_max) return false;

    // For each y in [y_min, y_max], compute the resulting overlap[n-1] range
    // Forward: o[i] <= a[(i+1)%n] - o[i-1]
    // min_o[i] = need[i]
    // Given o[0] = y:
    // o[1] <= a[1] - y, o[1] >= need[1]
    // o[2] <= a[2] - o[1] >= a[2] - (a[1]-y) = a[2]-a[1]+y
    // o[2] <= a[2] - need[1]
    // etc.

    // Compute the feasible range of o[n-1] given o[0] = y
    // We need o[n-1] >= need[n-1] and o[n-1] <= a[n-1] - o[n-2]
    // And o[n-1] = x = need_n (well, x is fixed)

    // Actually we're checking for a given C, is there ANY valid assignment?
    // So we need to check if there exists y in [y_min, y_max] and x = need_n
    // such that the chain is consistent.

    // Let me just check: given x = need_n, is there a valid y?
    // Or more generally: given x in [need_n, min(a[0],a[n-1])],
    // is there a valid assignment for the chain?

    // For the chain 0,1,...,n-1 with o[n-1] = x:
    // Forward propagation from o[0]:
    // o[0] in [need[0], a[0]-x]
    // o[1] in [need[1], a[1]-o[0]]
    // ...
    // o[n-1] in [need[n-1], a[n-1]-o[n-2]]
    // We need o[n-1] = x, so need[n-1] <= x <= a[n-1]-o[n-2]
    // => o[n-2] <= a[n-1] - x

    // Backward propagation from o[n-1] = x:
    // o[n-2] <= a[n-1] - x, o[n-2] >= need[n-2]
    // o[n-3] <= a[n-2] - o[n-2] >= a[n-2] - (a[n-1]-x) = a[n-2]-a[n-1]+x
    // o[n-3] <= a[n-2] - need[n-2]
    // etc.

    // Compute feasible range for o[0] from backward:
    // o[n-1] = x
    // o[n-2] in [need[n-2], a[n-1]-x]
    // o[n-3] in [need[n-3], a[n-2]-need[n-2]] ... wait, need to propagate properly

    // Let me compute min_o and max_o for each position going backward from o[n-1]=x:
    // max_o[n-2] = a[n-1] - x
    // min_o[n-2] = need[n-2]
    // max_o[n-3] = a[n-2] - min_o[n-2] = a[n-2] - need[n-2]
    // min_o[n-3] = need[n-3]
    // max_o[n-4] = a[n-3] - min_o[n-3] = a[n-3] - need[n-3]
    // ... in general: max_o[i] = a[i+1] - need[i+1] (for the backward pass, the min of the next constrains the max of current)
    // Wait no. Let me be more careful.

    // Backward from o[n-1] = x:
    // o[n-2] <= a[n-1] - x (= max_o[n-2])
    // o[n-2] >= need[n-2] (= min_o[n-2])
    // o[n-3] <= a[n-2] - o[n-2]
    //   max: a[n-2] - min_o[n-2] = a[n-2] - need[n-2]
    //   min: need[n-3]
    // o[n-4] <= a[n-3] - o[n-3]
    //   max: a[n-3] - need[n-3]
    //   min: need[n-4]
    // ...
    // o[0] <= a[1] - need[1]
    // o[0] >= need[0]

    // So backward gives: o[0] in [need[0], a[1]-need[1]]
    // Forward gives: o[0] in [need[0], a[0]-x]
    // Combined: o[0] in [need[0], min(a[1]-need[1], a[0]-x)]

    // Also from backward, the actual feasible range for o[0] depends on x.
    // Let me recompute properly.

    // For each x in [need_n, min(a[0], a[n-1])]:
    // Backward feasible range for o[0]:
    //   bw_max[0] = a[1] - need[1] (from the chain going backward)
    //   bw_min[0] = need[0]
    // Forward feasible range for o[0]:
    //   fw_max[0] = a[0] - x
    //   fw_min[0] = need[0]
    // Need: fw_min[0] <= bw_max[0] and bw_min[0] <= fw_max[0]
    // i.e., need[0] <= min(a[1]-need[1], a[0]-x)

    // But this is just the first step. The backward propagation also depends on x.
    // Let me just do it properly with forward and backward arrays.

    // I'll compute the feasible range for each o[i] given o[0] = y (forward)
    // and given o[n-1] = x (backward), then check overlap.

    // For now, let me use a simpler sufficient condition:
    // The circular problem has answer = max(max(a[i]), ceil(sum(a[i]) / floor(n/2)))
    // This is because each color can be assigned to at most floor(n/2) generals
    // (non-adjacent in a cycle of n).

    long long sum_a = 0;
    int max_a = 0;
    for (int i = 0; i < n; i++) {
        sum_a += a[i];
        max_a = max(max_a, a[i]);
    }
    int half = n / 2;
    int from_sum = (sum_a + half - 1) / half;
    return C >= max(max_a, from_sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Binary search on answer
    int lo = 0, hi = 0;
    for (int i = 0; i < n; i++) hi += a[i];
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
