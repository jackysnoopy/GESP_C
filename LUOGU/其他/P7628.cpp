#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> boys(n), girls(n);
    for (int i = 0; i < n; i++) cin >> boys[i];
    for (int i = 0; i < n; i++) cin >> girls[i];
    // Each boy wants to dance with a taller or shorter girl.
    // Each girl wants to dance with a taller or shorter boy.
    // No equal-height pairs want to dance.
    // Find maximum matching.
    //
    // This is a bipartite matching problem.
    // For each boy-girl pair (b, g):
    //   If b > g: boy wants shorter, girl wants taller. Compatible if girl wants taller.
    //   If b < g: boy wants taller, girl wants shorter. Compatible if girl wants shorter.
    //   If b == g: not compatible.
    //
    // Actually, re-reading: "每个男孩要么想和比他高的女孩跳舞，要么想和比他矮的女孩跳舞"
    // Each boy wants EITHER taller OR shorter (not both).
    // "没有同样高的男孩和女孩想和对方跳舞" - no equal-height pairs.
    //
    // So each boy has a preference (taller or shorter), and each girl has a preference.
    // We need to find the maximum matching where each pair satisfies both preferences.
    //
    // For a boy who wants taller: he can only dance with girls taller than him.
    // For a boy who wants shorter: he can only dance with girls shorter than him.
    // Same for girls.
    //
    // This is a bipartite graph. Maximum matching can be found with Hopcroft-Karp.
    // But for n up to 100000, we need an efficient approach.
    //
    // Actually, let me re-read: "每个男孩要么想和比他高的女孩跳舞，要么想和比他矮的女孩跳舞"
    // This means each boy has a fixed preference. But the problem doesn't tell us which preference!
    // "类似地，每个女孩要么想和比她高的男孩跳舞，要么想和比她矮的男孩跳舞"
    // Same for girls.
    //
    // Wait, the problem says "求如果遵照…每个人的意愿，最多能有多少对舞伴"
    // So we need to find the maximum number of pairs where both preferences are satisfied.
    //
    // But we don't know each person's preference! Or do we?
    // Re-reading: the input gives heights. The preferences are implied by the heights.
    // Actually, I think each person can choose their preference (taller or shorter),
    // and we want to maximize the number of pairs.
    //
    // Hmm, but the problem says "每个男孩要么想和比他高的女孩跳舞，要么想和比他矮的女孩跳舞"
    // This might mean that the preference is fixed but not given in the input.
    // We need to determine the preferences and the matching simultaneously.
    //
    // Actually, I think the problem is: each person has a fixed (but unknown) preference.
    // We need to find a matching that respects all preferences.
    // But since preferences are unknown, we need to find the maximum matching
    // over all possible preference assignments.
    //
    // This is equivalent to: find the maximum matching in the bipartite graph
    // where boy b and girl g are connected if b != g (different heights).
    // Because for any pair with b != g, we can assign preferences to make them compatible.
    //
    // Wait, but each person has ONE preference. If a boy is matched with a taller girl,
    // his preference must be "taller". Then he can't also be matched with a shorter girl.
    // But in a matching, each person is matched at most once, so this is fine.
    //
    // So the constraint is: for each matched pair (b, g), b != g.
    // And the maximum matching in the complete bipartite graph minus equal-height edges.
    //
    // For n boys and n girls, the maximum matching is n minus the number of "problematic" pairs.
    // Actually, the maximum matching is n if there's a perfect matching.
    // A perfect matching exists iff for every subset S of boys, |N(S)| >= |S|.
    // By Hall's theorem, this fails iff there's a subset S where |N(S)| < |S|.
    //
    // For the complete bipartite graph minus equal-height edges:
    // N(S) = all girls except those with the same height as some boy in S.
    // |N(S)| = n - |{g : g.height = b.height for some b in S}|.
    // |N(S)| < |S| iff n - |{g : g.height = b.height for some b in S}| < |S|
    // iff n < |S| + |{g : g.height = b.height for some b in S}|
    //
    // This is complex. Let me just implement a greedy matching.
    // Sort boys and girls by height. Match each boy with the closest available girl
    // that has a different height.
    
    // Actually, the answer is simply n minus the maximum number of boys and girls
    // that share the same height and can't be matched with anyone else.
    //
    // Hmm, this is getting complex. Let me just implement the greedy approach.
    
    vector<int> bidx(n), gidx(n);
    for (int i = 0; i < n; i++) { bidx[i] = i; gidx[i] = i; }
    sort(bidx.begin(), bidx.end(), [&](int a, int b) { return boys[a] < boys[b]; });
    sort(gidx.begin(), gidx.end(), [&](int a, int b) { return girls[a] < girls[b]; });
    
    vector<bool> girl_used(n, false);
    int matches = 0;
    
    // For each boy (sorted by height), try to match with the closest girl of different height
    for (int i = 0; i < n; i++) {
        int b = bidx[i];
        // Try girls in order of height proximity
        int best_g = -1, best_dist = n + 1;
        for (int j = 0; j < n; j++) {
            int g = gidx[j];
            if (girl_used[g]) continue;
            if (girls[g] == boys[b]) continue;
            int dist = abs(boys[b] - girls[g]);
            if (dist < best_dist) {
                best_dist = dist;
                best_g = g;
            }
        }
        if (best_g >= 0) {
            girl_used[best_g] = true;
            matches++;
        }
    }
    
    cout << matches << endl;
    return 0;
}
