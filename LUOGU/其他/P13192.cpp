#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string digits[] = {"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};
    // Unique order: Z(0), W(2), U(4), X(6), G(8), O(1), H(3), F(5), S(7), I(9)
    int order[] = {0,2,4,6,8,1,3,5,7,9};
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        int cnt[26] = {};
        for (char c : s) cnt[c - 'A']++;
        string result;
        for (int t = 0; t < 10; t++) {
            int d = order[t];
            int freq = 0;
            // Find a unique character for this digit
            if (d == 0) freq = cnt['Z' - 'A'];
            else if (d == 2) freq = cnt['W' - 'A'];
            else if (d == 4) freq = cnt['U' - 'A'];
            else if (d == 6) freq = cnt['X' - 'A'];
            else if (d == 8) freq = cnt['G' - 'A'];
            else if (d == 1) freq = cnt['O' - 'A'];
            else if (d == 3) freq = cnt['H' - 'A'];
            else if (d == 5) freq = cnt['F' - 'A'];
            else if (d == 7) freq = cnt['S' - 'A'];
            else if (d == 9) freq = cnt['I' - 'A'];
            for (int i = 0; i < freq; i++) result += (char)('0' + d);
            for (char c : digits[d]) cnt[c - 'A'] -= freq;
        }
        cout << "Case #" << tc << ": " << result << "\n";
    }
    return 0;
}
