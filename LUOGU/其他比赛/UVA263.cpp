#include <iostream>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

long long next_num(long long n) {
    string s = to_string(n);
    string desc = s, asc = s;
    sort(desc.begin(), desc.end(), greater<char>());
    sort(asc.begin(), asc.end());
    return stoll(desc) - stoll(asc);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    bool first_case = true;
    while (cin >> n && n != 0) {
        if (!first_case) cout << "\n";
        first_case = false;

        cout << "原始数字是 " << n << "\n";

        set<long long> seen;
        seen.insert(n);
        int len = 0;
        long long cur = n;
        while (true) {
            long long nxt = next_num(cur);
            len++;
            cout << nxt << "\n";
            if (seen.count(nxt)) {
                cout << "链长为 " << len << "\n";
                break;
            }
            seen.insert(nxt);
            cur = nxt;
        }
    }

    return 0;
}
