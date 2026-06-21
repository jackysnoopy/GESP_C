#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;

    int j_count = 0, o_count = 0, i_count = 0;
    int ans = 0;

    for (char c : S) {
        if (c == 'J') j_count++;
        else if (c == 'O') o_count++;
        else i_count++;
    }

    int joi = min({j_count, o_count, i_count});
    int ioi = min({o_count / 2, i_count});

    cout << joi + ioi << "\n";
    return 0;
}
