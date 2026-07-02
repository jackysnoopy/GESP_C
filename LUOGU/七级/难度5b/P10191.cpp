#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Tube {
    string layers;
    int top() const { return layers.empty() ? 0 : layers.back() - '0'; }
    int bot() const { return layers.empty() ? 0 : layers[0] - '0'; }
    int sz() const { return (int)layers.size(); }
    void pourTo(Tube& dest) {
        int color = top();
        int cnt = 0;
        for (int i = (int)layers.size() - 1; i >= 0; i--) {
            if (layers[i] - '0' == color) cnt++;
            else break;
        }
        dest.layers.append(layers.end() - cnt, layers.end());
        layers.erase(layers.end() - cnt, layers.end());
    }
    bool uniform() const {
        if (layers.empty()) return true;
        for (int i = 1; i < (int)layers.size(); i++)
            if (layers[i] != layers[0]) return false;
        return true;
    }
};

int countSegs(const string& s) {
    if (s.empty()) return 0;
    int c = 1;
    for (int i = 1; i < (int)s.size(); i++)
        if (s[i] != s[i-1]) c++;
    return c;
}

int solveMin(const string& f, const string& s) {
    int s1 = countSegs(f), s2 = countSegs(s);
    if (s1 <= 1 && s2 <= 1) return 0;
    int t1 = f.back()-'0', t2 = s.back()-'0';
    int b1 = f[0]-'0', b2 = s[0]-'0';
    if (s1 <= 1 && s2 > 1) return (t2 == t1) ? s2-1 : s2+1;
    if (s1 > 1 && s2 <= 1) return (t1 == t2) ? s1-1 : s1+1;
    if (t1 == t2 && b1 == b2) return s1+s2+1;
    if (t1 == t2 && b1 != b2) return s1+s2-1;
    if (t1 != t2 && b1 == b2) return s1+s2;
    return s1+s2-1;
}

void solve() {
    int n, p;
    cin >> n >> p;
    string f, s;
    cin >> f >> s;
    int m = solveMin(f, s);
    if (p == 1) { cout << m << "\n"; return; }

    Tube w[3];
    w[0].layers = f;
    w[1].layers = s;
    vector<pair<int,int>> moves;

    for (int iter = 0; iter < 10*n+100; iter++) {
        if (w[0].uniform() && w[1].uniform() && w[2].layers.empty()) break;

        int bi = -1, bj = -1, bsc = -1e9;
        for (int i = 0; i < 3; i++) {
            if (w[i].layers.empty()) continue;
            int tc = w[i].top();
            for (int j = 0; j < 3; j++) {
                if (j == i) continue;
                bool canMerge = w[j].layers.empty() || w[j].top() == tc;
                if (!canMerge) continue;
                Tube ti = w[i], tj = w[j];
                ti.pourTo(tj);
                bool tiU = ti.uniform(), tjU = tj.uniform();
                bool empty3 = w[2].layers.empty();
                bool complete = tiU && tjU;
                if (i < 2 && j < 2) complete = complete && empty3;
                else if (i < 2 && j == 2) complete = complete && w[3-i-1].uniform();
                else if (i == 2 && j < 2) complete = complete && w[3-j-1].uniform();

                int sc = 0;
                if (complete) {
                    sc = 100000;
                } else if (i < 2 && j < 2) {
                    sc = 100;
                    if (w[i].bot() != tc) sc += 50;
                    if (tiU) sc += 200;
                    if (tjU) sc += 200;
                } else if (i < 2 && j == 2) {
                    sc = 30;
                    if (w[i].bot() != tc) sc += 100;
                    if (tiU) sc += 200;
                } else {
                    sc = 60;
                    if (!w[j].layers.empty() && tc == w[j].bot()) sc += 50;
                    if (tjU) sc += 200;
                }
                if (sc > bsc) { bsc = sc; bi = i; bj = j; }
            }
        }
        if (bi >= 0) {
            w[bi].pourTo(w[bj]);
            moves.push_back({bi+1, bj+1});
            continue;
        }
        for (int i = 0; i < 3; i++) {
            if (!w[i].layers.empty()) {
                int j = (i+1)%3;
                w[i].pourTo(w[j]);
                moves.push_back({i+1, j+1});
                break;
            }
        }
    }

    int limit = (p == 2) ? m + 5 : m;
    while ((int)moves.size() > limit) moves.pop_back();
    cout << (int)moves.size() << "\n";
    for (auto& mv : moves) cout << mv.first << " " << mv.second << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
