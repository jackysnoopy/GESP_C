#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int parent[105];
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void unite(int x, int y) { parent[find(x)] = find(y); }

// 检查字符串中每个字母是否连续
bool is_valid(const string& s) {
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != s[i-1]) {
            for (int k = i + 1; k < (int)s.size(); k++) {
                if (s[k] == s[i-1]) return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<string> s(n);
        for (int i = 0; i < n; i++) cin >> s[i];

        // 检查每个字符串内部字母是否连续
        bool valid = true;
        for (int i = 0; i < n && valid; i++) {
            if (!is_valid(s[i])) valid = false;
        }

        if (!valid) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        // 初始化并查集
        for (int i = 0; i < n; i++) parent[i] = i;

        // 对于每个字母，包含它的所有字符串必须在同一个块中
        map<char, vector<int>> char_strings;
        for (int i = 0; i < n; i++) {
            for (char c : s[i]) {
                if (char_strings[c].empty() || char_strings[c].back() != i) {
                    char_strings[c].push_back(i);
                }
            }
        }

        for (auto& p : char_strings) {
            auto& vec = p.second;
            for (int k = 1; k < (int)vec.size(); k++) {
                unite(vec[0], vec[k]);
            }
        }

        // 按块分组
        map<int, vector<int>> block_members;
        for (int i = 0; i < n; i++) {
            block_members[find(i)].push_back(i);
        }

        vector<string> result_parts;
        bool ok = true;

        for (auto& p : block_members) {
            auto& members = p.second;
            int sz = members.size();

            if (sz == 1) {
                result_parts.push_back(s[members[0]]);
                continue;
            }

            // 块内拓扑排序
            vector<vector<int>> adj(sz);
            vector<int> indeg(sz, 0);
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    if (i == j) continue;
                    if (s[members[i]].back() == s[members[j]].front()) {
                        adj[i].push_back(j);
                        indeg[j]++;
                    }
                }
            }

            vector<int> order;
            vector<int> q;
            for (int i = 0; i < sz; i++) {
                if (indeg[i] == 0) q.push_back(i);
            }
            for (int qi = 0; qi < (int)q.size(); qi++) {
                int u = q[qi];
                order.push_back(u);
                for (int v : adj[u]) {
                    indeg[v]--;
                    if (indeg[v] == 0) q.push_back(v);
                }
            }

            if ((int)order.size() != sz) {
                ok = false;
                break;
            }

            string block_str = "";
            for (int idx : order) {
                block_str += s[members[idx]];
            }

            // 检查拼接后是否合法
            if (!is_valid(block_str)) {
                ok = false;
                break;
            }

            result_parts.push_back(block_str);
        }

        if (!ok) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        // 块之间拓扑排序
        int nb = result_parts.size();
        vector<char> block_first(nb), block_last(nb);
        for (int i = 0; i < nb; i++) {
            block_first[i] = result_parts[i].front();
            block_last[i] = result_parts[i].back();
        }

        vector<vector<int>> badj(nb);
        vector<int> bindeg(nb, 0);
        for (int i = 0; i < nb; i++) {
            for (int j = 0; j < nb; j++) {
                if (i == j) continue;
                if (block_last[i] == block_first[j]) {
                    badj[i].push_back(j);
                    bindeg[j]++;
                }
            }
        }

        vector<int> border;
        vector<int> bq;
        for (int i = 0; i < nb; i++) {
            if (bindeg[i] == 0) bq.push_back(i);
        }
        for (int qi = 0; qi < (int)bq.size(); qi++) {
            int u = bq[qi];
            border.push_back(u);
            for (int v : badj[u]) {
                bindeg[v]--;
                if (bindeg[v] == 0) bq.push_back(v);
            }
        }

        if ((int)border.size() != nb) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        string result = "";
        for (int idx : border) {
            result += result_parts[idx];
        }

        // 最终检查
        if (!is_valid(result)) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
            continue;
        }

        cout << "Case #" << t << ": " << result << "\n";
    }

    return 0;
}
