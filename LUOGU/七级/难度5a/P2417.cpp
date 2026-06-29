#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 20005;

vector<int> graph[MAXN];
int match[MAXN];
bool visited[MAXN];

bool dfs(int u) {
    for (int v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int m, n;
        cin >> m >> n;
        
        for (int i = 1; i <= m; i++) {
            graph[i].clear();
        }
        
        for (int i = 1; i <= m; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int p;
                cin >> p;
                graph[i].push_back(p);
            }
        }
        
        memset(match, -1, sizeof(match));
        
        int matched = 0;
        for (int i = 1; i <= m; i++) {
            memset(visited, false, sizeof(visited));
            if (dfs(i)) {
                matched++;
            }
        }
        
        cout << (matched == m ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
