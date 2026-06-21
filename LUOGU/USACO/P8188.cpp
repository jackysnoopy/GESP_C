#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int M, N, K;
        cin >> M >> N >> K;
        vector<int> f(N);
        for (int i = 0; i < N; i++) cin >> f[i];
        
        // Simulate the filing process
        // Screen shows K folders and K emails at a time
        // Can only scroll down. Email list shifts up when filing.
        
        // For each email in order, check if we can file it:
        // 1. Its folder must be visible (in the current K folders)
        // 2. It must be visible (in the current K emails)
        
        // The folder scroll position can only go down.
        // The email scroll position can only go down, UNLESS we're viewing
        // the last K emails and file one, which shifts the view up.
        
        // Greedy: process emails in order. For each email:
        //   - Scroll folders until the target folder is visible
        //   - If we can't scroll (already at max), check if it's visible
        //   - Scroll emails until this email is visible
        //   - File it
        
        // Key insight: we process emails in order 1..N.
        // The email view starts at 1..K.
        // When we file email i, emails after i shift up.
        // If we're viewing the last K emails and file one, the view shifts up by 1.
        
        // For each email i (1-indexed), we need to determine:
        // - At what "real position" does it appear?
        // - Is its folder visible?
        
        // The real position of email i = i - (number of emails filed before i that are before i)
        // Since we file in order, all emails before i have been filed.
        // So real position of email i = 1 (it's the first remaining email).
        
        // Wait, we file emails in order 1, 2, 3, ... So when we file email i,
        // all emails 1..i-1 have been filed. Email i is the first remaining.
        // It's always at position 1 in the email list.
        
        // So the email is always visible (position 1 is always in view 1..K).
        // The only constraint is the folder visibility.
        
        // But wait, we might not be able to scroll folders to the target.
        // The folder scroll starts at 1. We can only scroll down.
        // For email i targeting folder f[i], we need f[i] to be in [folder_scroll..folder_scroll+K-1].
        
        // If f[i] >= folder_scroll: we might need to scroll down.
        // If f[i] < folder_scroll: we can't scroll up. FAIL.
        
        // So the algorithm:
        // folder_scroll starts at 1.
        // For each email i:
        //   If f[i] < folder_scroll: we need to scroll emails to get a "reset"
        //     But emails can only reset if we're viewing the last K.
        //     Since we file in order, email i is always at position 1.
        //     We're always viewing the first K remaining emails.
        //     So we're never at the "last K" unless there are <= K remaining.
        //     If N-i+1 <= K: we're at the last K. Filing shifts view.
        //     But this doesn't help with folder scrolling.
        
        // Actually, re-reading the problem: the folder scroll and email scroll are independent.
        // We can scroll folders independently of emails.
        // The constraint: folders only scroll DOWN.
        
        // So for each email i:
        //   We need f[i] in [folder_scroll, folder_scroll + K - 1].
        //   If not, scroll folders down until f[i] is visible.
        //   If f[i] < folder_scroll: IMPOSSIBLE (can't scroll up).
        
        // But wait, we might have filed some emails whose folders are above f[i].
        // Those folders are still visible (folder scroll hasn't changed).
        
        // Actually, the folder scroll is independent. We just need to ensure
        // f[i] >= folder_scroll at all times.
        
        bool possible = true;
        int folder_scroll = 1;
        for (int i = 0; i < N; i++) {
            if (f[i] < folder_scroll) {
                possible = false;
                break;
            }
            while (f[i] > folder_scroll + K - 1) {
                folder_scroll++;
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    return 0;
}
