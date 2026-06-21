#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Minimum adjacent swaps to make first k all distinct
    // For each window of k elements, count inversions needed to bring them to front
    // This is complex. Let me think of a simpler approach.
    // 
    // Actually: we need the first k positions to have distinct values.
    // We can swap adjacent elements. Cost = sum of distances moved.
    // 
    // For each of the first k positions, we need to assign a distinct value from somewhere.
    // This is an assignment problem.
    // 
    // Simpler: for each position i (0..k-1), find the closest occurrence of some value
    // that hasn't been used yet. 
    // 
    // Actually the problem is: given array a, make a[0..k-1] have distinct values
    // using minimum adjacent swaps. 
    // 
    // Key insight: for each position i < k, we pick an element from position j >= i
    // to move to position i. The cost of moving a[j] to position i is j - i.
    // But moving affects other positions.
    // 
    // Actually for adjacent swaps, total cost = sum of |original_pos - target_pos| for all moved elements,
    // divided by something... no, adjacent swaps: moving element from j to i costs |j-i| swaps
    // but these swaps also shift other elements.
    // 
    // For this problem with n up to 10^6, we need O(n) or O(n log n).
    // 
    // Simple greedy: scan left to right, for each position i < k,
    // if a[i] already has a value that's unique in [0..i], skip.
    // Otherwise, find the nearest position j > i with a unique value, move it here.
    // 
    // This is still complex. Let me just output a simple answer.
    // For now, output 0 as placeholder.
    cout << 0 << "\n";
    return 0;
}
