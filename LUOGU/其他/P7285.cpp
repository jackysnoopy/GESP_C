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
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // left1[i] = consecutive 1s ending at position i
        // right1[i] = consecutive 1s starting at position i
        vector<int> left1(n, 0), right1(n, 0);
        for (int i = 0; i < n; i++) {
            left1[i] = (a[i] == 1) ? (i > 0 ? left1[i-1] + 1 : 1) : 0;
        }
        for (int i = n-1; i >= 0; i--) {
            right1[i] = (a[i] == 1) ? (i < n-1 ? right1[i+1] + 1 : 1) : 0;
        }
        
        // prefix ones
        vector<int> po(n+1, 0);
        for (int i = 0; i < n; i++) po[i+1] = po[i] + a[i];
        
        // Maximize: left1[l-1] + ones[l..r] + right1[r+1] over all 0 <= l <= r < n
        // = (left1[l-1] - po[l]) + (po[r+1] + right1[r+1])
        // Track best (left1[l-1] - po[l]) as l increases, and for each r compute total.
        
        int max_val = 0;
        int best_l = 0, best_r = -1;
        int max_left_contrib = 0;
        int max_left_l = 0;
        
        for (int r = 0; r < n; r++) {
            int val = max_left_contrib + po[r+1] + right1[r+1];
            if (val > max_val) {
                max_val = val;
                best_l = max_left_l;
                best_r = r;
            }
            int cand = left1[r] - po[r+1];
            if (cand > max_left_contrib) {
                max_left_contrib = cand;
                max_left_l = r + 1;
            }
        }
        
        // max_val = x - y for the optimal window
        // But we also need to check: what if NOT flipping any window is better?
        // max_val is already initialized to 0 (no flip), so that's covered.
        // However, if all elements are 1, max_val might be n (correct).
        // If all are 0, max_val stays 0 (correct, no flip needed, x=0, y=0).
        
        // But wait, what if there's an existing long run of 1s and no flip improves it?
        // max_val = 0 covers the "don't flip" case.
        // If existing max run is, say, 5, and flipping doesn't help, max_val might be < 5.
        // But x-y = 5 - 0 = 5 for not flipping. We need to consider this.
        
        // Actually, "not flipping" = empty window. For empty window, x = max consecutive 1s, y = 0.
        // x - y = max consecutive 1s.
        // We need to compare this with the flip case.
        
        int no_flip_x = 0, cur_run = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) { cur_run++; no_flip_x = max(no_flip_x, cur_run); }
            else cur_run = 0;
        }
        
        // For the flip case: x = left_ext + window_len + right_ext, y = zeros_in_window
        // x - y = max_val (which we computed).
        // But we also need the actual x and y separately to output.
        
        int final_x, final_y;
        vector<int> result(a);
        
        if (no_flip_x >= max_val) {
            // Don't flip anything
            final_x = no_flip_x;
            final_y = 0;
            // result = a (already set)
        } else {
            // Flip window [best_l, best_r]
            int left_ext = (best_l > 0) ? left1[best_l - 1] : 0;
            int right_ext = (best_r < n-1) ? right1[best_r + 1] : 0;
            int win_len = best_r - best_l + 1;
            int ones_in_win = po[best_r+1] - po[best_l];
            int zeros_in_win = win_len - ones_in_win;
            final_x = left_ext + win_len + right_ext;
            final_y = zeros_in_win;
            for (int i = best_l; i <= best_r; i++) result[i] = 1;
        }
        
        cout << final_x - final_y << "\n";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    return 0;
}
