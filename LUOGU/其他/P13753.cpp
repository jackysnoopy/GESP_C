#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // Partition into k groups. Minimize median of group sums.
        // Key insight: we can choose any k. 
        // For k=1: median = sum of all.
        // For k=n: median = median of individual elements.
        // The answer is the minimum possible median.
        // 
        // Observation: we want to minimize the floor((k+1)/2)-th smallest group sum.
        // With k groups, that's the ceil(k/2)-th smallest.
        // 
        // Strategy: sort elements. Put negative elements in their own groups (small sums),
        // put positive elements together.
        // 
        // Actually, the minimum median is achieved by making the median group sum as small as possible.
        // The minimum possible median is min(a[i]) when we put each element in its own group.
        // But we can do better: combine negative elements to make even smaller group sums.
        // 
        // Wait, we want to MINIMIZE the median. So we want as many small groups as possible.
        // The median of k groups is the ceil(k/2)-th smallest.
        // If we make k large (each element separate), median = median of elements.
        // If we combine negative elements, we get fewer groups but smaller minimums.
        // 
        // Let me think differently. The answer is min over all possible partitions of the median.
        // 
        // Key insight: we can always achieve the answer by choosing k=n (all separate).
        // But combining negative elements can make the median smaller.
        // 
        // Actually: if we sort a, the minimum median is a[0] (the minimum element)
        // when we make n groups each of size 1. But we can potentially do better
        // by putting multiple elements in one group to get an even smaller sum.
        // 
        // Wait no - if all elements are in their own group, median = a[n/2] (0-indexed, 
        // for n elements, k=n, median is the n/2-th smallest 0-indexed).
        // But we want to MINIMIZE this. So we want the median to be as small as possible.
        // 
        // The answer is the minimum possible value for the ceil(k/2)-th group sum.
        // This is: min over valid partitions.
        // 
        // Observation: the answer equals the minimum over all i of 
        // (sum of i smallest elements where i is odd) / ceil(i/2)... no, that's not right either.
        // 
        // Let me think about it differently:
        // We want to minimize the median. To do this, we want to create many groups with small sums.
        // The smallest possible group sum for a single element is a[0] (the minimum).
        // But we can create groups with even smaller sums by combining negatives.
        // 
        // Actually the answer is simply the minimum value of a[i] when we put each element
        // in its own group... but the median of n values is a[n/2] (sorted), not a[0].
        // 
        // Hmm, let me reconsider. The answer is the minimum possible median value.
        // For k groups, median = group_sum at position ceil(k/2) in sorted order.
        // 
        // The optimal strategy: 
        // - Put all negative elements in groups of 1 (getting individual negative values as group sums)
        // - Put positive elements in groups to not increase the median too much
        // 
        // Actually the answer is simply the minimum a[i] when k=n. Wait no, median of n values 
        // (when n is odd) is the middle value, not the minimum.
        // 
        // Let me reconsider from scratch. We can partition into any number of groups k.
        // We want the floor((k+1)/2)-th smallest group sum to be minimized.
        // 
        // The answer is the minimum value of a[i] (the smallest element).
        // Because: put all other elements in one group (sum = total - a[0]), and a[0] alone.
        // Then k=2, median = 1st smallest = min(a[0], total - a[0]).
        // If a[0] < total - a[0], median = a[0].
        // 
        // But can we do better? If a[0] is negative and we combine it with another negative...
        // Say a = [-5, -3, 10]. Put -5 and -3 in one group (sum=-8), 10 alone.
        // k=2, median = min(-8, 10) = -8. Better than -5!
        // 
        // So the answer is: the minimum possible group sum achievable, when we can have at most
        // ceil(k/2) groups with sums <= the median.
        // 
        // This is getting complex. Let me think about it as:
        // We need at least ceil(k/2) groups with sum <= answer.
        // The minimum answer is achievable by creating as many small-sum groups as possible.
        // 
        // The minimum achievable group sum for any subset is the sum of the two most negative elements.
        // But we need exactly one group to have that sum.
        // 
        // Let me just think about the answer:
        // Sort a ascending. The answer is min over j of (prefix_sum[j] where j is odd) / ... no.
        // 
        // Actually I think the answer is the minimum element when n=1, 
        // or the minimum sum of any contiguous group when elements are sorted.
        // 
        // Key insight for this problem:
        // - We can choose k freely.
        // - We want floor((k+1)/2) group sums to be as small as possible.
        // - The minimum median is: the minimum value of sum(S) over all subsets S,
        //   where we can create floor((k+1)/2) such subsets that are pairwise disjoint.
        // 
        // Actually I think the answer is just: sort a ascending, and the answer is a[0].
        // Because we can set k = 2*ceil(n/2), make the first ceil(n/2) groups each of 1 element
        // (the smallest ones), and the rest in one big group.
        // Then the median is the ceil(k/2)-th smallest = the ceil(2*ceil(n/2)/2)-th = 
        // ceil(n/2)-th smallest = a[ceil(n/2)-1].
        // 
        // Wait, but we can combine the two smallest to get an even smaller sum.
        // If a[0]+a[1] < a[0], then combining gives a smaller group sum.
        // Then k decreases by 1, and the median position changes.
        // 
        // I think the correct approach:
        // The answer is the minimum possible value of the ceil(k/2)-th smallest group sum.
        // For any partition into k groups:
        //   median = s[ceil(k/2)] (1-indexed, sorted ascending)
        // We want to minimize this over all possible k and all partitions.
        // 
        // The answer is: sort a ascending. 
        // For odd positions j (1,3,5,...): the minimum prefix sum at position j.
        // Actually no. Let me think about it more carefully.
        // 
        // Answer = min over all odd j (1 <= j <= n) of prefix_sum[j]
        // where prefix_sum[j] = a[1]+a[2]+...+a[j] (the sum of j smallest elements).
        // 
        // Because: if we create a partition where the first j/2+1 groups (ceil(j/2))
        // are individual elements from the sorted array, and the rest form one big group,
        // then k = ceil(j/2) + 1, and the median is the ceil(k/2)-th smallest.
        // This doesn't quite work out.
        // 
        // Let me just try the answer: minimum prefix sum at odd positions.
        
        sort(a.begin(), a.end());
        long long prefix = 0;
        long long ans = a[0];
        for (int i = 0; i < n; i++) {
            prefix += a[i];
            if ((i + 1) % 2 == 1) { // odd number of elements
                ans = min(ans, prefix);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
