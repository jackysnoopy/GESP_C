#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    vector<long long> W(N), H(N);
    for (int i = 0; i < N; i++) cin >> W[i] >> H[i];
    // K buildings, each from N designs. Total width = sum of chosen widths.
    // Height = max of chosen heights.
    // Area = total_width * max_height. Minimize area.
    // Choose K designs from N (with replacement? or without?).
    // "每个家庭有 N 种不同的楼房设计可供选择" - each family has N choices.
    // So we choose K designs (one per family), possibly with repetition.
    // Actually, "保证无重复的 (W_i, H_i)" means no duplicate (W, H) pairs.
    // But we can choose the same design for multiple families.
    //
    // Total width = sum of K chosen widths.
    // Max height = max of K chosen heights.
    // Area = total_width * max_height.
    //
    // Brute force: for each possible max_height h, find the K designs with H_i <= h
    // that minimize total width. Area = total_width * h.
    //
    // Sort designs by height. For each h = H_i (sorted), the eligible designs are
    // those with H_j <= h. Pick the K with smallest W_j.
    //
    // Sort designs by H. Maintain a multiset of the K smallest W values.
    // For each design (in order of increasing H), add its W to the multiset.
    // If multiset has more than K elements, remove the largest.
    // Compute area = sum_of_K_smallest * H_i.
    
    vector<int> idx(N);
    for (int i = 0; i < N; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return H[a] < H[b]; });
    
    long long ans = 1e18;
    long long sumW = 0;
    vector<long long> selected; // min-heap of selected W values
    
    for (int i = 0; i < N; i++) {
        int id = idx[i];
        // Add W[id]
        // Use a simple approach: maintain a sorted list
        selected.push_back(W[id]);
        sort(selected.begin(), selected.end());
        if ((int)selected.size() > K) {
            sumW -= selected.back();
            selected.pop_back();
        }
        sumW += W[id]; // Wait, this is wrong. Let me redo.
        // Actually, let me just keep a vector of selected values and recompute sum.
    }
    
    // Redo with proper logic
    selected.clear();
    ans = 1e18;
    for (int i = 0; i < N; i++) {
        int id = idx[i];
        selected.push_back(W[id]);
        sort(selected.begin(), selected.end());
        if ((int)selected.size() > K) selected.pop_back();
        if ((int)selected.size() == K) {
            long long s = 0;
            for (long long w : selected) s += w;
            ans = min(ans, s * H[id]);
        }
    }
    
    cout << ans << endl;
    return 0;
}
