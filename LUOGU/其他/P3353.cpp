#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, w;
    cin >> n >> w;
    // Stars at positions with brightness
    vector<int> cnt(100002, 0);
    for (int i = 0; i < n; i++) {
        int x, b;
        cin >> x >> b;
        cnt[x] += b;
    }
    // Sliding window of width w
    // Window [L, L+w] covers positions L to L+w (inclusive, since W is odd >= 3)
    // Actually: window covers L to L+W. W is odd, centered.
    // Or: positions from L to L+W inclusive = W+1 positions? 
    // "我们看到的星星也包括窗户边缘的星星"
    // Window of width W: covers [L, L+W] (W+1 positions) or [L, L+W-1] (W positions)?
    // Since W is odd and >= 3, the window is W positions wide.
    // Let's say window covers [L, L+W-1].
    int maxSum = 0;
    int curSum = 0;
    for (int i = 1; i <= 100000; i++) {
        curSum += cnt[i];
        if (i > w) curSum -= cnt[i - w - 1];
        maxSum = max(maxSum, curSum);
    }
    cout << maxSum << "\n";
    return 0;
}
