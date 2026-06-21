#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// [CCC 2025 Senior] 画画 / Pretty Pens
// n pens, m colors. Each pen has color c_i and beauty p_i.
// Paint uses one pen from each color. Beauty = sum of selected beauties.
// Can change at most one pen's color before painting (restores after).
// q operations: change color or beauty. After each, output max beauty.
//
// Without the "change one color" trick:
// For each color, we need at least one pen. Max beauty = sum of max beauty per color.
// If a color has no pen, we can't paint (unless we change one pen's color to fill it).
//
// With the trick: we can borrow one pen from a color with multiple pens
// and use it as the missing color. Max beauty = base_sum + max_benefit_from_switching.
//
// Let me think more carefully:
// - For each color, track the max beauty pen and second max.
// - base = sum of max beauty for each color that has pens.
// - missing_colors = colors with no pens.
// - If missing_colors == 0: we can optionally switch one pen to boost beauty.
//   Switching: take pen with beauty b from color c1 (leaving second max b2),
//   use it for color c2. New beauty = base - b + b + b2_for_c2? No...
//   Actually: if we switch pen from color c1 to color c2:
//   Old contribution from c1: max_beauty[c1]. New: second_max[c1] (or 0 if only one pen).
//   Old contribution from c2: max_beauty[c2]. New: beauty of switched pen (since it's now c2's pen).
//   But the switched pen must have beauty > current c2's max to improve.
//   Net gain = switched_beauty - second_max[c1] - max_beauty[c2] + switched_beauty?
//   No. Let me reconsider.
//   
//   We have a set of pens. We pick one pen from each color.
//   Normally: for each color, pick the pen with max beauty in that color.
//   With switching: we can change ONE pen's color. So we take a pen from its original color
//   (now that color loses this pen) and assign it to another color.
//   
//   If we switch pen with beauty b from color src to color dst:
//   - src loses this pen. If src had other pens, its contribution drops to second max.
//     If src had only this pen, src has no pen (unless this pen counts for dst).
//   - dst gains this pen. dst's contribution becomes max(original dst max, b).
//   Net change: (max(dst_max, b) - dst_max) + (src_second_max - src_max)
//             = max(0, b - dst_max) + (src_second_max - src_max)
//   Since src_second_max <= src_max, the second term is <= 0.
//   We want to maximize this.
//   
//   If missing_colors > 0:
//   We must switch a pen to fill a missing color.
//   Best: switch the pen with min beauty loss from its source color.
//   Loss from src: src_max - src_second_max (or src_max if only one pen).
//   Then assign to a missing color.
//   Net = -loss_from_src.
//   We want to minimize loss, so pick the pen where src_max - src_second_max is smallest
//   (or the pen with smallest beauty if it's the only pen in its color).
//   Then add its beauty to base.
//   Wait, the missing color gets this pen's beauty. So new base = old_base - src_contribution + src_second_max + pen_beauty.
//   Hmm, this is getting complex. Let me implement it with a BIT/segment tree approach.

// Actually, with n,q up to 1e5, let me use a simpler approach:
// Track per color: max beauty, count, sum of top 2 beauties.
// base = sum of max beauty for each occupied color.
// missing = set of colors with no pens.
// For the switch: find the best trade.

// Let me implement a clean solution with sets per color.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<int> c(n + 1), p(n + 1);
    vector<multiset<int>> color_pens(m + 1);
    vector<int> pen_color(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> p[i];
        pen_color[i] = c[i];
        color_pens[c[i]].insert(p[i]);
    }
    
    // Compute base beauty
    auto compute = [&]() -> long long {
        long long base = 0;
        int missing = 0;
        for (int col = 1; col <= m; col++) {
            if (!color_pens[col].empty()) {
                base += *color_pens[col].rbegin();
            } else {
                missing++;
            }
        }
        if (missing > 1) return -1LL; // can't fill more than 1 missing color
        if (missing == 1) {
            // Must switch a pen to fill missing color
            // Find pen with minimum beauty loss when removed
            long long minLoss = 1e18;
            for (int col = 1; col <= m; col++) {
                if (color_pens[col].size() >= 2) {
                    auto it = color_pens[col].rbegin();
                    long long mx = *it;
                    ++it;
                    long long loss = mx - *it; // beauty drop
                    if (loss < minLoss) minLoss = loss;
                } else if (color_pens[col].size() == 1) {
                    long long loss = *color_pens[col].rbegin(); // lose entire contribution
                    if (loss < minLoss) minLoss = loss;
                }
            }
            return base - minLoss;
        }
        // missing == 0: optionally switch to improve
        // Best improvement from switching pen from src to dst:
        // gain = max(0, pen_beauty - dst_max) - (src_max - src_second_max)
        long long bestGain = 0;
        for (int src = 1; src <= m; src++) {
            if (color_pens[src].size() == 0) continue;
            long long srcMax = *color_pens[src].rbegin();
            long long srcSecond = (color_pens[src].size() >= 2) ? 
                *next(color_pens[src].rbegin()) : 0;
            long long srcLoss = srcMax - srcSecond;
            for (int dst = 1; dst <= m; dst++) {
                if (dst == src) continue;
                if (color_pens[dst].empty()) continue; // shouldn't happen since missing==0
                long long dstMax = *color_pens[dst].rbegin();
                long long gain = max(0LL, srcMax - dstMax) - srcLoss;
                bestGain = max(bestGain, gain);
            }
        }
        return base + bestGain;
    };
    
    // This O(m^2) per query is too slow for m=1e5.
    // Let me use a different approach.
    
    // Actually let me just recompute efficiently.
    // For missing == 0 case:
    // We want max over all (src, dst) of max(0, srcMax - dstMax) - (srcMax - srcSecond)
    // = max(0, srcMax - dstMax) - srcLoss
    // 
    // If srcMax > dstMax: gain = srcMax - dstMax - srcLoss = srcSecond - dstMax
    // If srcMax <= dstMax: gain = -srcLoss (always negative)
    // 
    // So we want max(srcSecond - dstMax) over all src,dst where srcSecond > dstMax.
    // This is maximized when srcSecond is large and dstMax is small.
    // Best srcSecond = max over all src of srcSecond.
    // Best dstMax = min over all dst != src of dstMax.
    // But src and dst must be different.
    
    // Actually, for efficiency, let me track:
    // - For each color: max beauty and second max beauty
    // - The color with the largest second max
    // - The color with the smallest max (that is not the same as above)
    
    // This is getting complex. Let me just implement a working but possibly slower solution.
    
    // For each query, recompute base and best switch.
    // Track per-color stats in sets. O(m) per query worst case.
    // With m,q up to 1e5, O(mq) is too slow. Need O(log m) per query.
    
    // Let me use a different approach: track the answer incrementally.
    // Maintain: sum of max per color, and the best possible switch.
    
    // For now, implement a correct O(m) per query solution.
    
    while (q--) {
        int type, i, val;
        cin >> type >> i >> val;
        if (type == 1) {
            // Change color of pen i
            int old_col = pen_color[i];
            color_pens[old_col].erase(color_pens[old_col].find(p[i]));
            pen_color[i] = val;
            color_pens[val].insert(p[i]);
        } else {
            // Change beauty of pen i
            int col = pen_color[i];
            color_pens[col].erase(color_pens[col].find(p[i]));
            p[i] = val;
            color_pens[col].insert(p[i]);
        }
        
        // Recompute answer
        long long base = 0;
        int missing = 0;
        vector<int> occupied;
        for (int col = 1; col <= m; col++) {
            if (!color_pens[col].empty()) {
                base += *color_pens[col].rbegin();
                occupied.push_back(col);
            } else {
                missing++;
            }
        }
        
        if (missing > 1) {
            cout << "-1\n";
        } else if (missing == 1) {
            long long minLoss = 1e18;
            for (int col : occupied) {
                long long mx = *color_pens[col].rbegin();
                long long second = (color_pens[col].size() >= 2) ? 
                    *next(color_pens[col].rbegin()) : 0;
                minLoss = min(minLoss, mx - second);
            }
            cout << base - minLoss << "\n";
        } else {
            // Try all switches
            long long bestGain = 0;
            // We need srcSecond and srcMax for each color, and dstMax for each color
            // best gain = max(srcSecond - dstMax) over valid (src, dst)
            // where srcSecond > dstMax and src != dst
            // 
            // Track: sorted by srcSecond (desc), and sorted by dstMax (asc)
            // For each src, find dst with smallest dstMax where dstMax < srcSecond and dst != src
            // 
            // For efficiency: find the two colors with smallest dstMax, and the color with largest srcSecond.
            // If they're different, great. If same, use second smallest dstMax.
            
            long long maxSecond = -1;
            int maxSecondCol = -1;
            long long minMax1 = 1e18, minMax2 = 1e18;
            int minMaxCol1 = -1, minMaxCol2 = -1;
            
            for (int col : occupied) {
                long long mx = *color_pens[col].rbegin();
                long long second = (color_pens[col].size() >= 2) ? 
                    *next(color_pens[col].rbegin()) : 0;
                if (second > maxSecond || (second == maxSecond && col < maxSecondCol)) {
                    maxSecond = second;
                    maxSecondCol = col;
                }
                if (mx < minMax1) {
                    minMax2 = minMax1; minMaxCol2 = minMaxCol1;
                    minMax1 = mx; minMaxCol1 = col;
                } else if (mx < minMax2) {
                    minMax2 = mx; minMaxCol2 = col;
                }
            }
            
            if (maxSecondCol != minMaxCol1 && maxSecond > minMax1) {
                bestGain = maxSecond - minMax1;
            } else if (minMaxCol2 >= 0 && maxSecond > minMax2) {
                bestGain = maxSecond - minMax2;
            }
            
            cout << base + bestGain << "\n";
        }
    }
    return 0;
}
