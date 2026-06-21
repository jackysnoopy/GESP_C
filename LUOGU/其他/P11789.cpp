#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// [JOI 2019 Final] 画展 / Exhibition
// N paintings (size S_i, beauty V_i), M frames (size C_j).
// Painting fits in frame if S_i <= C_j.
// Arrange paintings in a row: frames non-decreasing, beauties non-decreasing.
// Each painting uses one frame. Maximize number of paintings displayed.
//
// Strategy: 
// 1. Sort paintings by beauty (ascending).
// 2. Sort frames by size (ascending).
// 3. Greedy: for each painting in order of beauty, find the smallest frame that fits.
//    Use a multiset of available frames. For each painting (in beauty order),
//    find the smallest frame >= S_i. If found, use it.
//    This ensures both beauty and frame size are non-decreasing.
//
// Wait, we need both constraints simultaneously. Let me think more carefully.
//
// After selecting k paintings and k frames:
// - Sort selected paintings by beauty: V_{p1} <= V_{p2} <= ... <= V_{pk}
// - Sort selected frames by size: C_{f1} <= C_{f2} <= ... <= C_{fk}
// - Each painting p_i must fit in frame f_i: S_{p_i} <= C_{f_i}
//
// So we need a matching where we can sort both by one criterion.
// 
// Approach: sort paintings by beauty. For each painting in order, assign a frame.
// The frame must be >= painting size. Among available frames, pick the smallest one >= size.
// This greedy works because:
// - Later paintings have higher beauty (non-decreasing by construction)
// - Using the smallest available frame preserves larger frames for future paintings
// - If a painting can't find a frame, all remaining (larger beauty) paintings also can't
//   (since they need frames too, and we're using the smallest available)
//
// Actually, the greedy isn't that simple because a painting with high beauty might have
// small size and fit in a small frame, while a later painting with even higher beauty
// might have large size. But since we process in beauty order and use smallest-fit frame,
// this should work.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    
    vector<pair<int,int>> paintings(N); // (beauty, size)
    for (int i = 0; i < N; i++) {
        cin >> paintings[i].second >> paintings[i].first;
    }
    
    vector<int> frames(M);
    for (int i = 0; i < M; i++) cin >> frames[i];
    
    // Sort paintings by beauty (ascending)
    sort(paintings.begin(), paintings.end());
    // Sort frames by size (ascending)
    sort(frames.begin(), frames.end());
    
    // Greedy: for each painting in beauty order, find smallest frame >= size
    multiset<int> available(frames.begin(), frames.end());
    int ans = 0;
    
    for (int i = 0; i < N; i++) {
        int size = paintings[i].second;
        auto it = available.lower_bound(size);
        if (it != available.end()) {
            available.erase(it);
            ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
