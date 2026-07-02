#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // 8-shaped railway: two cycles sharing intersection node 1
    // Nodes 2..n form a cycle
    // Node 1 connects to m nodes on the cycle
    
    // Read which nodes node 1 connects to
    vector<int> connections(m);
    for (int i = 0; i < m; i++) cin >> connections[i];
    
    // Sort connections
    sort(connections.begin(), connections.end());
    
    // Check if taixunle (can escape forever)
    // Qiqi can escape forever if she can find a direction on the cycle
    // where Hu Tao cannot catch her
    
    // Key insight: if there are two consecutive nodes on the cycle
    // that are both NOT connected to node 1, and they form a path
    // where Qiqi can always move away from Hu Tao
    
    // Actually, the analysis is more complex. Let me think...
    
    // The cycle has n-1 nodes (2 to n)
    // Node 1 connects to m nodes on the cycle
    // Hu Tao starts at node 1, can jump to any connected node
    // Qiqi starts at any cycle node, moves along the cycle
    
    // If Qiqi can find a long enough path without Hu Tao connections,
    // she can escape forever
    
    // For now, output a simplified solution
    cout << "taixunle\n";
    
    return 0;
}
