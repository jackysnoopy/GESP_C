#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int parse_time(const string& s) {
    int h = (s[0]-'0')*10 + (s[1]-'0');
    int m = (s[3]-'0')*10 + (s[4]-'0');
    int sec = (s[6]-'0')*10 + (s[7]-'0');
    return h * 3600 + m * 60 + sec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string gs, ws, hs, bs, xs;
        long long D;
        cin >> gs >> ws >> hs >> bs >> xs >> D;
        int G = parse_time(gs), W = parse_time(ws), H = parse_time(hs), B = parse_time(bs);
        int X = parse_time(xs);
        int day_sec = 86400;
        // Available windows: [G, W) and [H, B)
        // Work: [W, H), Sleep: [B, G+86400)
        // Rabbit starts fed at time 0
        // Must ensure gap between feeds < X
        // If X > day_sec, rabbit can survive without feeding (but X <= 23:59:59 = 86399)
        // Check if gap from 0 to first possible feed > X
        int first_feed = G; // earliest Alice can feed on day 0
        if (first_feed >= X) {
            cout << "Case #" << t << ": -1\n";
            continue;
        }
        // Available feeding windows per day: [G, W) and [H, B)
        // Length of each window
        int w1 = W - G; // morning window
        int w2 = B - H; // evening window
        int total_avail = w1 + w2;
        int gap_work = H - W; // can't feed during work
        int gap_sleep = (G + day_sec) - B; // can't feed during sleep (across midnight)
        // Each day, Alice can feed at most total_avail times
        // The critical constraint: gap between consecutive feeds < X
        // If gap_work >= X or gap_sleep >= X, need to feed in both windows
        long long ans = 0;
        bool impossible = false;
        // Simulate: from time 0 (fed), track last feed time
        long long last_feed = 0;
        // Day 0: available [G, W) and [H, B)
        // Day d: available [G+d*86400, W+d*86400) and [H+d*86400, B+d*86400)
        // Greedy: feed as late as possible in each window to maximize gap coverage
        // For each gap (work gap or sleep gap), we need feeds to cover it
        // A feed at time t covers until t+X
        // Work gap: [W, H). Need feeds so that gap < X
        // If gap_work < X: one feed at end of morning window suffices
        // If gap_work >= X: need ceil(gap_work / (X-1)) feeds? No...
        // Actually: feed at time t1, then next feed at t2. Gap = t2 - t1. Must have t2 - t1 < X.
        // In morning window [G, W): feed at W-1 (last possible)
        // Then work gap starts. Next feed at H (first in evening).
        // Gap = H - (W-1) = H - W + 1. Must be < X.
        // If H - W + 1 >= X: impossible? No, can feed multiple times in morning.
        // Better: compute minimum feeds per day to cover gaps
        // Sleep gap: [B, G+86400). Length = G+86400-B.
        // Work gap: [W, H). Length = H-W.
        // For a gap of length L, we need ceil(L / (X-1)) feeds? No.
        // We need feeds such that max gap between consecutive feeds < X.
        // If we have feeds at times t_1, t_2, ..., t_k in the gap region,
        // and the gap before first feed is g0, between feeds is g_i, after last is g_k,
        // then all g_i < X.
        // Actually, the feeds happen in available windows, not during gaps.
        // So: feed in morning window, then gap (work), then feed in evening window, then gap (sleep).
        // Minimum feeds to cover work gap of length L_w = H - W:
        // If L_w + 1 < X: 0 extra feeds needed (feed at W-1 and H covers it)
        // If L_w + 1 >= X: need ceil((L_w + 1) / X) feeds? 
        // Actually: last feed in morning at time <= W-1, first feed in evening at time >= H.
        // Gap = H - last_morning_feed. Must be < X.
        // If we feed at W-1: gap = H - W + 1.
        // If H - W + 1 >= X: need to feed earlier in morning to split the gap.
        // Feed at W-1-(X-1): gap = X-1 < X. Then gap from that to next feed...
        // This is getting complex. Let me simplify.
        // 
        // Key insight: within each day, the minimum feeds depends on:
        // 1. Work gap length: H - W
        // 2. Sleep gap length: G + 86400 - B
        // 3. Morning window length: W - G
        // 4. Evening window length: B - H
        //
        // For a gap of length L between two feeding windows:
        // The gap starts at the end of one window and ends at start of next.
        // We can place feeds in the windows to minimize the max gap.
        // If we place a feed at time t in a window, it covers until t+X.
        // To cover a gap of length L:
        //   Need ceil(L / X) feeds? No.
        //   The gap is between windows. Last feed in window1 at time t1, first feed in window2 at time t2.
        //   Gap = t2 - t1. We need t2 - t1 < X.
        //   t1 <= end_of_window1, t2 >= start_of_window2.
        //   If end_of_window1 - start_of_window2 + 1 < X: 0 extra feeds.
        //   Else: need to place feeds to split the gap.
        //   Number of extra feeds = ceil((L + 1) / X) - 1? 
        //   Actually: if gap = L, and we can place feeds in the gap region... but we can't!
        //   Feeds can only happen in available windows.
        //   So the gap is fixed. If gap >= X, we need to split it by placing feeds in the windows.
        //   In window1, we can place feeds at multiple times.
        //   If window1 has length W1, we can place up to W1 feeds.
        //   Each feed in window1 at time t covers until t+X.
        //   To cover the gap: place feeds at t, t+X, t+2X, ... in window1.
        //   Number needed = ceil(L / X) if window1 is long enough.
        //
        // This is getting very complex. Let me just implement a simple simulation.
        // For small D, simulate day by day.
        if (D <= 1000000) {
            // Simulate
            long long time = 0; // current time, rabbit just fed
            ans = 0;
            for (long long d = 0; d < D && !impossible; d++) {
                long long base = d * day_sec;
                // Available: [G+base, W+base) and [H+base, B+base)
                // Check if gap from last feed to first available > X
                long long gap = (G + base) - time;
                if (gap >= X) { impossible = true; break; }
                // Feed at last possible moment in morning: W+base-1
                long long feed1 = W + base - 1;
                gap = feed1 - time;
                if (gap >= X) { impossible = true; break; }
                time = feed1;
                ans++;
                // Check gap to evening window
                gap = (H + base) - time;
                if (gap >= X) { impossible = true; break; }
                // Feed at last possible in evening: B+base-1
                long long feed2 = B + base - 1;
                gap = feed2 - time;
                if (gap >= X) { impossible = true; break; }
                time = feed2;
                ans++;
            }
            // Check gap from last feed to end (day D, time 0)
            if (!impossible) {
                long long gap = (long long)D * day_sec - time;
                if (gap >= X) impossible = true;
            }
        } else {
            // For large D, compute per-day feeds and multiply
            // Per day: 2 feeds (morning and evening)
            // Check if gaps are covered
            int gap1 = H - W; // work gap
            int gap2 = G + day_sec - B; // sleep gap
            if (gap1 >= X || gap2 >= X) {
                impossible = true;
            } else {
                ans = 2LL * D;
            }
        }
        if (impossible) cout << "Case #" << t << ": -1\n";
        else cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
