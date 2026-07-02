#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<int> children[MAXN];
int parent[MAXN];
int subtreeSize[MAXN];

// 计算子树大小
void dfs(int u) {
    subtreeSize[u] = 1;
    for (int v : children[u]) {
        dfs(v);
        subtreeSize[u] += subtreeSize[v];
    }
}

// 查找特殊节点
int findSpecial(int u) {
    // 如果当前节点就是特殊节点
    if (ask(u) == 1) {
        // 检查是否是叶子节点或者子树中只有这一个特殊节点
        bool hasSpecialChild = false;
        for (int v : children[u]) {
            if (ask(v) == 1) {
                hasSpecialChild = true;
                break;
            }
        }
        if (!hasSpecialChild) {
            return u;
        }
    }
    
    // 在子树中查找
    for (int v : children[u]) {
        if (ask(v) == 1) {
            return findSpecial(v);
        }
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 这里是交互题的框架，实际实现需要根据交互库调整
    // 以下为示例代码
    
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }
    
    // 计算子树大小
    dfs(1);
    
    // 查找特殊节点
    int result = findSpecial(1);
    cout << "! " << result << endl;
    
    return 0;
}