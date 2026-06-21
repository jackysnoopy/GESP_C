#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

const string target = "123804765";
const int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start;
    if (!(cin >> start)) return 0;
    if (start == target) { cout << 0 << '\n'; return 0; }

    unordered_map<string, int> dist;
    queue<string> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        string cur = q.front(); q.pop();
        int d = dist[cur];
        int pos = (int)cur.find('0');
        int r = pos / 3, c = pos % 3;
        for (auto& dir : dirs) {
            int nr = r + dir[0], nc = c + dir[1];
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
            int npos = nr * 3 + nc;
            string nxt = cur;
            swap(nxt[pos], nxt[npos]);
            if (nxt == target) { cout << d + 1 << '\n'; return 0; }
            if (!dist.count(nxt)) { dist[nxt] = d + 1; q.push(nxt); }
        }
    }
    cout << -1 << '\n';
    return 0;
}
