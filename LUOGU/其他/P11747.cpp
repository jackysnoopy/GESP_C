#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> spf(1000001, 0);

void sieve() {
    for (int i = 2; i <= 1000000; i++) {
        if (spf[i] == 0) {
            for (int j = i; j <= 1000000; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

int countOps(int x) {
    if (x <= 1) return 0;
    int cnt = 0;
    while (x > 1) {
        int p = spf[x];
        while (x % p == 0) x /= p;
        cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    vector<int> pref(1000001, 0);
    for (int i = 1; i <= 1000000; i++) {
        pref[i] = pref[i-1] + countOps(i);
    }
    vector<long long> ans_to_num(63, -1);
    for (int i = 2; i <= 1000000; i++) {
        int ops = countOps(i);
        if (ops <= 62 && ans_to_num[ops] == -1) {
            ans_to_num[ops] = i;
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            cout << countOps(x) << "\n";
        } else {
            int q;
            cin >> q;
            cout << ans_to_num[q] << "\n";
        }
    }
    return 0;
}
