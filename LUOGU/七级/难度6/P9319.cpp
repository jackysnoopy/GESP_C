#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2e5 + 5;

vector<int> adj[MAXN];
bool visited[MAXN];
int match[MAXN];

bool dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

void SocialEngineering(int n, int m, vector<pair<int,int>> edges) {
    // 初始化邻接表
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        match[i] = -1;
    }
    
    for (auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 尝试找到完美匹配
    int matching = 0;
    for (int i = 1; i <= n; i++) {
        memset(visited, false, sizeof(visited));
        if (dfs(i)) matching++;
    }
    
    // 如果存在完美匹配，玛丽亚有必胜策略
    if (matching == n / 2) {
        return; // 直接返回，玛丽亚必胜
    }
    
    // 否则，尝试让玛丽亚输
    while (true) {
        int move = GetMove();
        if (move == 0) {
            // 玛丽亚认输
            return;
        }
        
        // 选择一个合法的回应
        // 这里需要更复杂的策略
        // 简单实现：选择第一个未访问的邻居
        bool found = false;
        for (int v : adj[move]) {
            if (match[v] == -1) {
                MakeMove(v);
                found = true;
                break;
            }
        }
        
        if (!found) {
            // 没有合法操作，让玛丽亚认输
            return;
        }
    }
}