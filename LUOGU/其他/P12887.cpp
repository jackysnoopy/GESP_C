#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;
    int same = 0, diff = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] == T[i]) same++;
        else diff++;
    }
    int ans = same + min(diff, M);
    cout << ans << "\n";
    return 0;
}
