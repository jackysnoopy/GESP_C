#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct State {
    int r, c, steps;
};

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int R, C, sr, sc, er, ec;
        cin >> R >> C >> sr >> sc >> er >> ec;
        sr--; sc--; er--; ec--;

        int dist[105][105][3];
        memset(dist, -1, sizeof(dist));

        queue<State> q;
        for (int d = 0; d < 3; d++) {
            dist[sr][sc][d] = 0;
            q.push({sr, sc, d});
        }

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty()) {
            State s = q.front(); q.pop();
            if (s.r == er && s.c == ec) {
                cout << "Case " << t << ": " << dist[s.r][s.c][s.steps % 3] << endl;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nr = s.r + dr[i];
                int nc = s.c + dc[i];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int ns = s.steps + 1;
                if (dist[nr][nc][ns % 3] == -1) {
                    dist[nr][nc][ns % 3] = dist[s.r][s.c][s.steps % 3] + 1;
                    q.push({nr, nc, ns});
                }
            }
        }
    }
    return 0;
}
