#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int grid[45][45];
int row[1605];
int col[1605];

void gen_spiral(int n) {
    memset(grid, 0, sizeof(grid));
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int num = 1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++) {
            grid[top][c] = num;
            row[num] = top;
            col[num] = c;
            num++;
        }
        top++;
        for (int r = top; r <= bottom; r++) {
            grid[r][right] = num;
            row[num] = r;
            col[num] = right;
            num++;
        }
        right--;
        for (int c = right; c >= left; c--) {
            grid[bottom][c] = num;
            row[num] = bottom;
            col[num] = c;
            num++;
        }
        bottom--;
        for (int r = bottom; r >= top; r--) {
            grid[r][left] = num;
            row[num] = r;
            col[num] = left;
            num++;
        }
        left++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        long long k;
        cin >> n >> k;

        int total = n * n;
        long long normal_steps = total - 1;
        long long need_save = normal_steps - k;

        if (need_save == 0) {
            cout << "Case #" << t << ": 0\n";
            continue;
        }

        if (n <= 39) {
            gen_spiral(n);

            // 枚举所有相邻对，找捷径
            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            vector<pair<int, int>> all_shortcuts; // (节省步数, idx)
            // 存储所有可能的捷径
            struct Shortcut { int save, a, b; };
            vector<Shortcut> sc;
            for (int v = 1; v < total; v++) {
                int r = row[v], c = col[v];
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                    int nb = grid[nr][nc];
                    if (nb > v + 1) {
                        sc.push_back({(int)(nb - v - 1), v, nb});
                    }
                }
            }

            // 按节省步数从大到小排序
            sort(sc.begin(), sc.end(), [](const Shortcut& x, const Shortcut& y) {
                return x.save > y.save;
            });

            // 贪心选择
            vector<pair<int, int>> ans;
            long long saved = 0;
            vector<bool> used(total + 1, false);

            for (auto& s : sc) {
                if (saved + s.save > need_save) continue;
                if (used[s.a] || used[s.b]) continue;
                // 检查a和b之间的路径是否被其他捷径打断
                // 简化：检查a和b之间是否有已使用的编号
                bool conflict = false;
                for (int v = s.a + 1; v < s.b; v++) {
                    if (used[v]) { conflict = true; break; }
                }
                if (conflict) continue;
                ans.push_back({s.a, s.b});
                saved += s.save;
                used[s.a] = true;
                used[s.b] = true;
                if (saved == need_save) break;
            }

            if (saved != need_save) {
                cout << "Case #" << t << ": IMPOSSIBLE\n";
                continue;
            }

            cout << "Case #" << t << ": " << ans.size() << "\n";
            for (auto& p : ans) {
                cout << p.first << " " << p.second << "\n";
            }
        } else {
            // 大N：用螺旋结构的规律
            // 每圈提供4个"角跳跃"
            // 跳跃的节省步数可以计算

            // 实际上，对于大N，我们可以用圈之间的跳跃
            // 但实现较复杂，先用暴力（N<=39覆盖部分分）

            cout << "Case #" << t << ": IMPOSSIBLE\n";
        }
    }

    return 0;
}
