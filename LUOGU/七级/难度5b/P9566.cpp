#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Block {
    int start, len;
    char c1, c2;
    bool has_c1, has_c2;
    int mn, mx;
};

int calcMax(int L, bool same) {
    if (same) return L + (L % 2);
    return L + (1 - L % 2);
}

bool canFill(int L, char c1, char c2, bool hc1, bool hc2, int v) {
    if (!hc1 && !hc2) return v >= 0 && v <= L - 1;
    if (!hc1 || !hc2) return v >= 0 && v <= L;
    if (c1 == c2) return v >= 0 && v <= calcMax(L, true) && v % 2 == 0;
    return v >= 1 && v <= calcMax(L, false) && v % 2 == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        int k;
        cin >> s >> k;
        int n = s.size();

        vector<Block> blocks;
        int base = 0;
        char lastFC = 0;
        int lastFP = -1;

        int i = 0;
        while (i < n) {
            if (s[i] == '?') {
                int j = i;
                while (j < n && s[j] == '?') j++;
                Block b;
                b.start = i;
                b.len = j - i;
                b.has_c1 = (i > 0);
                b.c1 = b.has_c1 ? s[i - 1] : 0;
                b.has_c2 = (j < n);
                b.c2 = b.has_c2 ? s[j] : 0;

                if (!b.has_c1 && !b.has_c2) {
                    b.mn = 0;
                    b.mx = n - 1;
                } else if (!b.has_c1 || !b.has_c2) {
                    b.mn = 0;
                    b.mx = b.len;
                } else {
                    if (b.c1 == b.c2) {
                        b.mn = 0;
                        b.mx = calcMax(b.len, true);
                    } else {
                        b.mn = 1;
                        b.mx = calcMax(b.len, false);
                    }
                }

                blocks.push_back(b);
                i = j;
            } else {
                if (lastFP >= 0 && lastFP == i - 1) {
                    base += (s[i] != lastFC) ? 1 : 0;
                }
                lastFC = s[i];
                lastFP = i;
                i++;
            }
        }

        int total_mn = base, total_mx = base;
        for (size_t t = 0; t < blocks.size(); t++) {
            total_mn += blocks[t].mn;
            total_mx += blocks[t].mx;
        }

        if (k < total_mn || k > total_mx) {
            cout << "Impossible\n";
            continue;
        }

        int D = k - base;
        vector<int> rem_mn(blocks.size() + 1, 0), rem_mx(blocks.size() + 1, 0);
        for (int t = (int)blocks.size() - 1; t >= 0; t--) {
            rem_mn[t] = rem_mn[t + 1] + blocks[t].mn;
            rem_mx[t] = rem_mx[t + 1] + blocks[t].mx;
        }

        vector<int> contrib(blocks.size());
        bool ok = true;
        for (size_t t = 0; t < blocks.size(); t++) {
            int need = D;
            int lo = max(blocks[t].mn, need - rem_mx[t + 1]);
            int hi = min(blocks[t].mx, need - rem_mn[t + 1]);

            if (blocks[t].has_c1 && blocks[t].has_c2) {
                int parity = (blocks[t].c1 == blocks[t].c2) ? 0 : 1;
                if (lo % 2 != parity) lo++;
                if (hi % 2 != parity) hi--;
            }

            if (lo > hi) { ok = false; break; }
            contrib[t] = lo;
            D -= lo;
        }

        if (!ok || D != 0) {
            cout << "Impossible\n";
            continue;
        }

        string result = s;
        for (size_t t = 0; t < blocks.size(); t++) {
            Block& b = blocks[t];
            int v = contrib[t];
            char prev = b.has_c1 ? b.c1 : 0;
            bool has_prev = b.has_c1;

            for (int j = 0; j < b.len; j++) {
                int rem_len = b.len - j - 1;
                bool has_next = b.has_c2;
                char next_c = b.c2;

                char ch = '0';
                int chg = (has_prev && prev != ch) ? 1 : 0;
                int rem_v = v - chg;

                bool feasible = false;
                if (rem_len == 0) {
                    if (!has_next) {
                        feasible = (rem_v == 0);
                    } else {
                        feasible = (rem_v == ((ch != next_c) ? 1 : 0));
                    }
                } else {
                    if (!has_next) {
                        feasible = (rem_v >= 0 && rem_v <= rem_len);
                    } else {
                        if (ch == next_c) {
                            feasible = (rem_v >= 0 && rem_v <= rem_len + (rem_len % 2) && rem_v % 2 == 0);
                        } else {
                            feasible = (rem_v >= 1 && rem_v <= rem_len + (1 - rem_len % 2) && rem_v % 2 == 1);
                        }
                    }
                }

                if (!feasible) ch = '1';

                result[b.start + j] = ch;
                v -= chg;
                prev = ch;
                has_prev = true;
            }
        }

        cout << result << "\n";
    }

    return 0;
}
