#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, string> parent;

string findAncestor(string a, int k) {
    string cur = a;
    for (int i = 0; i < k; i++) {
        if (parent.find(cur) == parent.end()) return "";
        cur = parent[cur];
    }
    return cur;
}

int main() {
    string line;
    parent.clear();
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "no.child") {
            string child, par;
            while (cin >> child >> par) {
                if (child == "no.child") break;
                parent[child] = par;
            }
            continue;
        }
    }
    
    string a, b;
    while (cin >> a >> b) {
        if (a == "no.child" && b == "no.child") break;
        string cur = a;
        int dist = 0;
        bool found = false;
        
        while (parent.find(cur) != parent.end()) {
            cur = parent[cur];
            dist++;
            if (cur == b) {
                cout << "child of " << b << "\n";
                found = true;
                break;
            }
            string cur2 = b;
            int dist2 = 0;
            while (parent.find(cur2) != parent.end()) {
                cur2 = parent[cur2];
                dist2++;
                if (cur2 == cur) {
                    if (dist2 == dist) cout << cur << " is the middle generation\n";
                    else if (dist2 > dist) cout << b << " is an ancestor of " << a << "\n";
                    else cout << a << " is an ancestor of " << b << "\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) cout << "no relation\n";
    }
    return 0;
}
