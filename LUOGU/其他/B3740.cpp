#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    cin >> x;
    // Board is 4x4, 16 bits. Top 8 = white(0), bottom 8 = black(1).
    // We need to swap adjacent tiles to get all 0s on top, 1s on bottom.
    // BFS on state space. State = 16-bit mask.
    // Target: upper 8 bits = 0, lower 8 bits = 1 => mask = 0b11111111 (lower 8)
    int target = (1 << 8) - 1; // 255
    if (x == target) { cout << 0 << "\n"; return 0; }
    vector<int> dist(1 << 16, -1);
    queue<int> q;
    dist[x] = 0;
    q.push(x);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        if (s == target) { cout << dist[s] << "\n"; return 0; }
        // Find positions of 0s and 1s
        for (int i = 0; i < 16; i++) {
            int r = i / 4, c = i % 4;
            int dr[] = {0, 0, 1, -1};
            int dc[] = {1, -1, 0, 0};
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
                int j = nr * 4 + nc;
                int bi = (s >> i) & 1;
                int bj = (s >> j) & 1;
                if (bi != bj) {
                    // Swap bits i and j
                    int ns = s;
                    ns ^= (1 << i);
                    ns ^= (1 << j);
                    if (dist[ns] == -1) {
                        dist[ns] = dist[s] + 1;
                        q.push(ns);
                    }
                }
            }
        }
    }
    return 0;
}
