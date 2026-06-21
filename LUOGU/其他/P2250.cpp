#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    long long rot = 0;
    bool flipped = false;
    vector<pair<char,long long>> ops;
    for (int i = 0; i < (int)s.size(); ) {
        char c = s[i++];
        long long num = 0;
        while (i < (int)s.size() && s[i]>='0' && s[i]<='9') {
            num = num*10 + (s[i]-'0');
            i++;
        }
        if (num == 0) num = 1;
        ops.push_back({c, num});
    }
    for (auto& op : ops) {
        if (op.first == 'r') {
            if (flipped) rot = ((rot - op.second%n) % n + n) % n;
            else rot = (rot + op.second) % n;
        } else {
            flipped = !flipped;
            rot = ((-rot) % n + n) % n;
        }
    }
    if (rot == 0 && !flipped) { cout << "\n"; return 0; }
    string res;
    if (rot != 0) res += "r" + to_string((int)rot);
    if (flipped) res += (res.empty() ? "" : " ") + string("m1");
    cout << res << "\n";
    return 0;
}
