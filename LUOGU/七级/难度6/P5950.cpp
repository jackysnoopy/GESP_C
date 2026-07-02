#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef __int128 lll;

void print(lll x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += char('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

lll read_lll() {
    string s;
    cin >> s;
    lll x = 0;
    for (char c : s) x = x * 10 + (c - '0');
    return x;
}

lll count_digit(int d, lll N) {
    if (N <= 0) return 0;
    lll result = 0;
    for (lll power = 1; power <= N; power *= 10) {
        lll higher = N / (power * 10);
        lll cur = (N / power) % 10;
        lll lower = N % power;
        if (d == 0) {
            if (higher == 0) continue;
            result += (higher - 1) * power;
            if (cur > 0) result += power;
            else result += lower + 1;
        } else {
            result += higher * power;
            if (cur > d) result += power;
            else if (cur == d) result += lower + 1;
        }
    }
    return result;
}

bool check(lll N, lll cnt[]) {
    for (int d = 0; d < 10; d++)
        if (count_digit(d, N) > cnt[d]) return false;
    return true;
}

int main() {
    lll cnt[10];
    for (int i = 0; i < 10; i++) cnt[i] = read_lll();

    lll lo = 0, hi = 1;
    while (check(hi, cnt)) {
        if (hi > (lll)1e38) break;
        hi *= 2;
    }
    while (lo < hi) {
        lll mid = lo + (hi - lo + 1) / 2;
        if (check(mid, cnt)) lo = mid;
        else hi = mid - 1;
    }
    print(lo);
    cout << "\n";
    return 0;
}
