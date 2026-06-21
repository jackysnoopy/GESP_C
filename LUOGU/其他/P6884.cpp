#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Node {
    bool isLeaf;
    char op;
    vector<Node*> ch;
    ~Node() { for (auto c : ch) delete c; }
};

string expr;
int pos;
int K;
vector<int> Z;

Node* parse() {
    while (pos < (int)expr.size() && expr[pos] == ' ') pos++;
    if (expr[pos] == '(') {
        pos++;
        Node* n = new Node();
        n->isLeaf = false;
        n->op = '+';
        n->ch.push_back(parse());
        while (pos < (int)expr.size() && expr[pos] != ')') {
            if (expr[pos] == '+' || expr[pos] == '*') {
                n->op = expr[pos++];
            }
            n->ch.push_back(parse());
        }
        pos++;
        if (n->ch.size() == 1 && n->op == '+') {
            Node* child = n->ch[0];
            n->ch.clear();
            delete n;
            return child;
        }
        return n;
    } else {
        pos++;
        Node* n = new Node();
        n->isLeaf = true;
        n->op = 0;
        return n;
    }
}

double solve(Node* n) {
    if (n->isLeaf) return (double)Z[1];
    int arity = (int)n->ch.size();
    double budget = (double)Z[arity];
    vector<double> mv;
    for (auto c : n->ch) mv.push_back(solve(c));
    double sumMax = 0;
    for (double v : mv) sumMax += v;
    if (n->op == '+') return min(sumMax, budget);
    // '*' node: maximize prod(x_i) s.t. sum(x_i) <= budget, 0 <= x_i <= mv[i]
    if (sumMax <= budget) {
        double prod = 1;
        for (double v : mv) prod *= v;
        return prod;
    }
    // Sort by mv descending
    sort(mv.begin(), mv.end(), greater<double>());
    // Compute prefix sums of mv
    vector<double> psum(arity + 1, 0);
    for (int i = 0; i < arity; i++) psum[i+1] = psum[i] + mv[i];
    
    // For each k (0..arity), try: fix first k at their max, distribute rest equally
    // But we also need to handle the case where equal distribution exceeds some child's cap.
    // The correct approach: binary search on lambda.
    // For a given lambda, the optimal x_i = min(mv[i], lambda).
    // We want sum(x_i) = budget (use full budget for max product).
    // sum(min(mv[i], lambda)) is monotone in lambda, so binary search.
    
    double lo = 0, hi = budget;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        double s = 0;
        for (int i = 0; i < arity; i++) {
            s += min(mv[i], mid);
        }
        if (s < budget) lo = mid;
        else hi = mid;
    }
    double lambda = hi;
    double prod = 1;
    for (int i = 0; i < arity; i++) {
        prod *= min(mv[i], lambda);
    }
    return prod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> K;
    Z.resize(K + 1);
    for (int i = 1; i <= K; i++) cin >> Z[i];
    cin >> ws;
    getline(cin, expr);
    pos = 0;
    Node* root = parse();
    printf("%.5f\n", solve(root));
    delete root;
    return 0;
}
