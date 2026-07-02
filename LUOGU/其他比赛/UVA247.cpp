#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
map<string, int> nameToIdx;
string idxToName[26];
int graph[26][26];

int main() {
    int cases = 0;
    while (cin >> n >> m && (n || m)) {
        cases++;
        if (cases > 1) cout << endl;
        
        nameToIdx.clear();
        int cnt = 0;
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                graph[i][j] = 0;
        
        for (int i = 0; i < m; i++) {
            string a, b;
            cin >> a >> b;
            if (nameToIdx.find(a) == nameToIdx.end()) {
                nameToIdx[a] = cnt;
                idxToName[cnt] = a;
                cnt++;
            }
            if (nameToIdx.find(b) == nameToIdx.end()) {
                nameToIdx[b] = cnt;
                idxToName[cnt] = b;
                cnt++;
            }
            graph[nameToIdx[a]][nameToIdx[b]] = 1;
        }
        
        for (int k = 0; k < cnt; k++)
            for (int i = 0; i < cnt; i++)
                for (int j = 0; j < cnt; j++)
                    if (graph[i][k] && graph[k][j])
                        graph[i][j] = 1;
        
        vector<bool> visited(cnt, false);
        vector<vector<string>> circles;
        
        for (int i = 0; i < cnt; i++) {
            if (visited[i]) continue;
            vector<int> component;
            for (int j = 0; j < cnt; j++) {
                if (graph[i][j] && graph[j][i])
                    component.push_back(j);
            }
            if (component.empty()) {
                component.push_back(i);
            }
            
            bool skip = false;
            for (int c : component) {
                if (visited[c]) { skip = true; break; }
            }
            if (skip) continue;
            
            for (int c : component) visited[c] = true;
            
            vector<string> names;
            for (int c : component)
                names.push_back(idxToName[c]);
            sort(names.begin(), names.end());
            circles.push_back(names);
        }
        
        cout << "Calling circles for data set " << cases << ":" << endl;
        for (auto& circle : circles) {
            for (int i = 0; i < (int)circle.size(); i++) {
                if (i > 0) cout << ", ";
                cout << circle[i];
            }
            cout << endl;
        }
    }
    return 0;
}
