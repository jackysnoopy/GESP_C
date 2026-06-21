#include <iostream>
#include <queue>
#include <map>
using namespace std;
int N, M, Si, Sj;
struct Node { int i, j; };
int dist[1000001];
Node from[1000001];
int exits[10001][2];
int encode(int i, int j) { return i*1000000+j; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> Si >> Sj;
    map<int,bool> isExit;
    for (int i = 0; i < M; i++) {
        cin >> exits[i][0] >> exits[i][1];
        isExit[encode(exits[i][0], exits[i][1])] = true;
    }
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= 2*N; j++) dist[encode(i,j)] = -1;
    queue<Node> q;
    int si = encode(Si, Sj);
    dist[si] = 0;
    q.push({Si, Sj});
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int ci = cur.i, cj = cur.j;
        int d = dist[encode(ci, cj)];
        int dir[3][2];
        // Triangle (i,j): if j is odd, neighbors are (i,j-1),(i,j+1),(i+1,j+1)
        // if j is even, neighbors are (i,j-1),(i,j+1),(i-1,j-1)
        if (cj % 2 == 1) {
            dir[0][0]=ci; dir[0][1]=cj-1;
            dir[1][0]=ci; dir[1][1]=cj+1;
            dir[2][0]=ci+1; dir[2][1]=cj+1;
        } else {
            dir[0][0]=ci; dir[0][1]=cj-1;
            dir[1][0]=ci; dir[1][1]=cj+1;
            dir[2][0]=ci-1; dir[2][1]=cj-1;
        }
        for (int k = 0; k < 3; k++) {
            int ni = dir[k][0], nj = dir[k][1];
            if (ni < 1 || ni > N) continue;
            if (nj < 1 || nj > 2*ni-1) continue;
            int ne = encode(ni, nj);
            if (dist[ne] == -1) {
                dist[ne] = d + 1;
                q.push({ni, nj});
            }
        }
    }
    int bestT = 1e9, bestI = -1, bestJ = -1;
    for (int i = 0; i < M; i++) {
        int ne = encode(exits[i][0], exits[i][1]);
        if (dist[ne] != -1 && dist[ne]+1 < bestT) {
            bestT = dist[ne]+1;
            bestI = exits[i][0];
            bestJ = exits[i][1];
        } else if (dist[ne] != -1 && dist[ne]+1 == bestT) {
            if (exits[i][0] < bestI || (exits[i][0]==bestI && exits[i][1]<bestJ)) {
                bestI = exits[i][0];
                bestJ = exits[i][1];
            }
        }
    }
    cout << bestI << " " << bestJ << "\n";
    return 0;
}
