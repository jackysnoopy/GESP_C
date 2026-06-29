#include <cstdio>
#include <algorithm>
#include <string>
#include <stack>
#include <iostream>
using namespace std;
struct Node {
    char type;
    int left, right;
    int min_rank, max_rank;
};
const int MAXN = 2000005;
Node nodes[MAXN];
int node_cnt = 0;
int parse(const string& s, int& pos) {
    int cur = node_cnt++;
    if (s[pos] == '?') {
        nodes[cur].type = '?';
        nodes[cur].min_rank = 1;
        nodes[cur].max_rank = 1;
        pos++;
        return cur;
    }
    if (s.substr(pos, 4) == "min(") {
        nodes[cur].type = 'm';
        pos += 4;
    } else {
        nodes[cur].type = 'M';
        pos += 4;
    }
    nodes[cur].left = parse(s, pos);
    pos++;
    nodes[cur].right = parse(s, pos);
    pos++;
    return cur;
}
void compute(int u) {
    if (nodes[u].type == '?') return;
    compute(nodes[u].left);
    compute(nodes[u].right);
    int l = nodes[u].left, r = nodes[u].right;
    if (nodes[u].type == 'm') {
        nodes[u].min_rank = min(nodes[l].min_rank, nodes[r].min_rank);
        nodes[u].max_rank = max(nodes[l].max_rank, nodes[r].max_rank);
    } else {
        nodes[u].min_rank = max(nodes[l].min_rank, nodes[r].min_rank);
        nodes[u].max_rank = min(nodes[l].max_rank, nodes[r].max_rank);
    }
}
int main() {
    string s;
    getline(cin, s);
    int pos = 0;
    int root = parse(s, pos);
    compute(root);
    int n = 0;
    for (int i = 0; i < node_cnt; i++) {
        if (nodes[i].type == '?') n++;
    }
    printf("%d\n", max(0, nodes[root].max_rank - nodes[root].min_rank + 1));
    return 0;
}