// UVA140 - Bandwidth (带宽)
// 找出最小带宽的顶点排列
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

int n;
char vertices[10];
int adj[26][26];
int pos[26];
int bestBandwidth;
char bestOrder[10];
char currentOrder[10];

void solve(int idx, int bandwidth) {
    if (idx == n) {
        if (bandwidth < bestBandwidth) {
            bestBandwidth = bandwidth;
            for (int i = 0; i < n; i++) {
                bestOrder[i] = currentOrder[i];
            }
        }
        return;
    }
    
    // 剪枝：如果当前带宽已经超过最优解
    if (bandwidth >= bestBandwidth) return;
    
    for (int i = 0; i < n; i++) {
        if (pos[vertices[i] - 'A'] != -1) continue;
        
        pos[vertices[i] - 'A'] = idx;
        currentOrder[idx] = vertices[i];
        
        // 计算新增带宽
        int newBandwidth = bandwidth;
        for (int j = 0; j < idx; j++) {
            if (adj[vertices[i] - 'A'][currentOrder[j] - 'A']) {
                int dist = idx - j;
                newBandwidth = std::max(newBandwidth, dist);
            }
        }
        
        solve(idx + 1, newBandwidth);
        pos[vertices[i] - 'A'] = -1;
    }
}

int main() {
    std::string line;
    
    while (std::getline(std::cin, line) && line != "#") {
        if (line.empty()) continue;
        
        // 初始化
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                adj[i][j] = 0;
            }
            pos[i] = -1;
        }
        n = 0;
        
        // 解析图
        std::string currentVertex;
        for (char c : line) {
            if (c == ';') {
                // 处理当前顶点的邻接关系
                if (!currentVertex.empty()) {
                    char v = currentVertex[0];
                    // 查找该顶点的邻接表
                    size_t pos = line.find(v + std::string(" ->"));
                    if (pos != std::string::npos) {
                        pos += 4; // 跳过 " ->"
                        while (pos < line.size() && line[pos] != ';') {
                            if (std::isalpha(line[pos])) {
                                adj[v - 'A'][line[pos] - 'A'] = 1;
                                adj[line[pos] - 'A'][v - 'A'] = 1;
                            }
                            pos++;
                        }
                    }
                    currentVertex.clear();
                }
            } else if (c == ':' || c == ' ') {
                if (!currentVertex.empty() && currentVertex.size() == 1) {
                    // 顶点定义
                    vertices[n++] = currentVertex[0];
                    currentVertex.clear();
                }
            } else if (std::isalpha(c)) {
                currentVertex += c;
            }
        }
        
        // 处理最后一个顶点
        if (!currentVertex.empty() && currentVertex.size() == 1) {
            vertices[n++] = currentVertex[0];
        }
        
        // 深度优先搜索找最小带宽
        bestBandwidth = INT_MAX;
        for (int i = 0; i < n; i++) {
            pos[vertices[i] - 'A'] = -1;
        }
        solve(0, 0);
        
        // 输出结果
        for (int i = 0; i < n; i++) {
            std::cout << bestOrder[i];
            if (i < n - 1) std::cout << " ";
        }
        std::cout << " -> " << bestBandwidth << std::endl;
    }
    
    return 0;
}
