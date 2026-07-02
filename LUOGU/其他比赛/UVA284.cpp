#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Component {
    int x1, y1, x2, y2;
};

int n;
vector<Component> comps;

bool intersect(const Component& a, const Component& b) {
    return !(a.x2 < b.x1 || b.x2 < a.x1 || a.y2 < b.y1 || b.y2 < a.y1);
}

int main() {
    int caseNum = 0;
    while (cin >> n && n) {
        comps.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> comps[i].x1 >> comps[i].y1 >> comps[i].x2 >> comps[i].y2;
            if (comps[i].x1 > comps[i].x2) swap(comps[i].x1, comps[i].x2);
            if (comps[i].y1 > comps[i].y2) swap(comps[i].y1, comps[i].y2);
        }
        
        if (caseNum++) cout << endl;
        cout << "Case " << caseNum << ":" << endl;
        
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(comps[i], comps[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << i << " <-> ";
            if (adj[i].empty()) {
                cout << "none";
            } else {
                for (int j = 0; j < adj[i].size(); j++) {
                    cout << adj[i][j] << (j == adj[i].size() - 1 ? "" : ", ");
                }
            }
            cout << endl;
        }
    }
    return 0;
}
