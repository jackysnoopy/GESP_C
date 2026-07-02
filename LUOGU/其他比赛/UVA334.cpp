#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, cas = 0;
    while (cin >> n >> m && (n || m)) {
        map<string, int> name2id;
        vector<string> id2name;
        for (int i = 0; i < n; i++) {
            string name; cin >> name;
            name2id[name] = i;
            id2name.push_back(name);
        }

        bool adj[305][305] = {};
        for (int i = 0; i < m; i++) {
            string a, b; cin >> a >> b;
            adj[name2id[a]][name2id[b]] = true;
        }

        // Floyd-Warshall
        bool reach[305][305] = {};
        for (int i = 0; i < n; i++) reach[i][i] = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                reach[i][j] = adj[i][j];

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (reach[i][k] && reach[k][j])
                        reach[i][j] = true;

        vector<pair<string, string>> concurrent;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (!reach[i][j] && !reach[j][i])
                    concurrent.push_back({id2name[i], id2name[j]});

        cout << "City being analyzed: " << ++cas << "\n";
        cout << concurrent.size() << " concurrent events:\n";
        for (auto& p : concurrent)
            cout << p.first << "," << p.second << " are concurrent.\n";
        cout << "\n";
    }
    return 0;
}
