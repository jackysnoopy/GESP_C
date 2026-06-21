#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string parse(const string& s, int& pos) {
    vector<string> children;
    pos++; // skip '('
    while (s[pos] == '(')
        children.push_back(parse(s, pos));
    pos++; // skip ')'
    
    sort(children.begin(), children.end());
    string res = "(";
    for (const string& c : children) res += c;
    res += ")";
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        string a, b; cin >> a >> b;
        int pa = 0, pb = 0;
        string ra = parse(a, pa);
        string rb = parse(b, pb);
        cout << (ra == rb ? "same" : "different") << "\n";
    }
    return 0;
}