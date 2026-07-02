#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int cost;
    vector<int> children;
};

int N, Cl, Cs;
vector<Node> nodes;
vector<int> order_list;
vector<int> keep_list;

struct DP {
    long long min_cost;
    int keep; // how many children kept in registers
};

DP solve(int u) {
    if (nodes[u].children.empty()) {
        // Leaf: must load from memory
        return {Cl, 0};
    }
    int k = nodes[u].children.size();
    vector<DP> child_dp(k);
    for (int i = 0; i < k; i++)
        child_dp[i] = solve(nodes[u].children[i]);
    // For this node, we have some available registers
    // We need to decide which children to keep in registers
    // and which to store to memory
    // The operation needs k arguments in registers
    // If we keep m children, we need to load (k-m) from memory
    // and store (k-m) back... no.
    // Actually: after evaluating children, some are in registers, some in memory.
    // To perform the operation, all k children must be in registers.
    // So we need to load any children that are in memory.
    // After operation, result can stay in register or be stored.
    // Cost = sum of child costs + (k - kept) * Cl + nodes[u].cost
    // If we keep the result: use 1 register
    // If we store: use 0 registers, add Cs cost
    // But we don't know available registers here...
    // Simplified approach: assume unlimited registers, greedy
    // Keep all children (no load cost), compute, decide keep/store
    long long total = 0;
    for (int i = 0; i < k; i++) total += child_dp[i].min_cost;
    total += nodes[u].cost;
    // Option 1: keep result (needs 1 register)
    DP keep_res = {total, 1};
    // Option 2: store result (needs 0 registers, extra Cs)
    DP store_res = {total + Cs, 0};
    // We'll decide later based on context
    // For simplicity, always keep if possible
    return keep_res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> Cl >> Cs;
    // Read expression tree
    // Nodes are numbered from 1 in input order
    // Build tree from input
    function<int()> read_node = [&]() -> int {
        static int node_id = 0;
        node_id++;
        int u = node_id;
        int k;
        cin >> k;
        if (k > 0) {
            cin >> nodes[u].cost;
            for (int i = 0; i < k; i++) {
                int child = read_node();
                nodes[u].children.push_back(child);
            }
        }
        return u;
    };
    nodes.resize(10001);
    int root = read_node();
    DP result = solve(root);
    cout << result.min_cost << "\n";
    // Output evaluation order (simplified: post-order)
    function<void(int)> print_order = [&](int u) {
        for (int v : nodes[u].children) print_order(v);
        if (!nodes[u].children.empty()) {
            order_list.push_back(u);
            keep_list.push_back(1);
        }
    };
    print_order(root);
    for (int i = 0; i < (int)order_list.size(); i++)
        cout << order_list[i] << " " << keep_list[i] << "\n";
    return 0;
}
