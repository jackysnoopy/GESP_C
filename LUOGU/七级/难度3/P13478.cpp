#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
map<string, vector<string>> ch;
map<string, bool> isMix;
int compute(const string& name) {
    if (!isMix.count(name) || !isMix[name]) return 0;
    vector<int> cb;
    for (const string& ing : ch[name])
        if (isMix.count(ing) && isMix[ing]) cb.push_back(compute(ing));
    sort(cb.begin(), cb.end(), greater<int>());
    int m = cb.size();
    int result = m + 1;
    for (int i = 0; i < m; i++) result = max(result, i + cb[i]);
    return result;
}
int main() {
    int C;
    cin >> C;
    for (int tc = 1; tc <= C; tc++) {
        int N;
        cin >> N;
        ch.clear(); isMix.clear();
        vector<string> names;
        for (int i = 0; i < N; i++) {
            string name; int M;
            cin >> name >> M;
            isMix[name] = true;
            names.push_back(name);
            for (int j = 0; j < M; j++) { string ing; cin >> ing; ch[name].push_back(ing); }
        }
        cout << "Case #" << tc << ": " << compute(names[0]) << "\n";
    }
    return 0;
}
