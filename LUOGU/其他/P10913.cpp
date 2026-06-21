#include <iostream>
#include <algorithm>
using namespace std;
int n, w, h;
struct Circle { int x, y, r; };
Circle c[1001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w >> h;
    for (int i = 0; i < n; i++) cin >> c[i].x >> c[i].y >> c[i].r;
    int ans = 0;
    // For each circle as bottom-left corner of rectangle
    // Check how many circles fit in w*h rectangle
    for (int i = 0; i < n; i++) {
        int bx = c[i].x - c[i].r;
        int by = c[i].y - c[i].r;
        // Try both orientations: w*h and h*w
        // Rectangle [bx, bx+w] x [by, by+h]
        int cnt1 = 0, cnt2 = 0;
        for (int j = 0; j < n; j++) {
            // Check if circle j fits in rectangle [bx, bx+w] x [by, by+h]
            if (c[j].x - c[j].r >= bx && c[j].x + c[j].r <= bx + w &&
                c[j].y - c[j].r >= by && c[j].y + c[j].r <= by + h)
                cnt1++;
            // Check if circle j fits in rectangle [bx, bx+h] x [by, by+w]
            if (c[j].x - c[j].r >= bx && c[j].x + c[j].r <= bx + h &&
                c[j].y - c[j].r >= by && c[j].y + c[j].r <= by + w)
                cnt2++;
        }
        ans = max(ans, max(cnt1, cnt2));
        // Also try with this circle at top-right
        bx = c[i].x + c[i].r - w;
        by = c[i].y + c[i].r - h;
        cnt1 = cnt2 = 0;
        for (int j = 0; j < n; j++) {
            if (c[j].x - c[j].r >= bx && c[j].x + c[j].r <= bx + w &&
                c[j].y - c[j].r >= by && c[j].y + c[j].r <= by + h)
                cnt1++;
            if (c[j].x - c[j].r >= bx && c[j].x + c[j].r <= bx + h &&
                c[j].y - c[j].r >= by && c[j].y + c[j].r <= by + w)
                cnt2++;
        }
        ans = max(ans, max(cnt1, cnt2));
    }
    cout << ans << "\n";
    return 0;
}
