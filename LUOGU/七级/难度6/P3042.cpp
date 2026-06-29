#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int N;
long long M, K;
vector<vector<long long>> cards;
map<pair<long long, int>, bool> memo;

bool canGuarantee(long long d, int i) {
    if (i == N) {
        return d <= K || (M - d <= K && d > 0);
    }
    auto key = make_pair(d, i);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    long long a1 = (1 + cards[i][0]) % M, b1 = cards[i][1] % M;
    long long a2 = (1 + cards[i][2]) % M, b2 = cards[i][3] % M;
    long long a3 = (1 + cards[i][4]) % M, b3 = cards[i][5] % M;
    long long a4 = (1 + cards[i][6]) % M, b4 = cards[i][7] % M;
    long long dt1 = (d * a1 + b1) % M;
    long long dt2 = (d * a2 + b2) % M;
    if (canGuarantee(dt1, i + 1) && canGuarantee(dt2, i + 1)) {
        return memo[key] = true;
    }
    long long db1 = (d * a3 + b3) % M;
    long long db2 = (d * a4 + b4) % M;
    return memo[key] = (canGuarantee(db1, i + 1) && canGuarantee(db2, i + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> K;
    string bessie;
    cin >> bessie;
    cards.resize(N, vector<long long>(8));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 8; j++)
            cin >> cards[i][j];
    string answer;
    long long d = 0;
    for (int i = 0; i < N; i++) {
        long long a1 = (1 + cards[i][0]) % M, b1 = cards[i][1] % M;
        long long a2 = (1 + cards[i][2]) % M, b2 = cards[i][3] % M;
        long long a3 = (1 + cards[i][4]) % M, b3 = cards[i][5] % M;
        long long a4 = (1 + cards[i][6]) % M, b4 = cards[i][7] % M;
        long long dt1 = (d * a1 + b1) % M;
        long long dt2 = (d * a2 + b2) % M;
        if (canGuarantee(dt1, i + 1) && canGuarantee(dt2, i + 1)) {
            answer += 'T';
            d = (bessie[i] == 'T') ? dt1 : dt2;
        } else {
            answer += 'B';
            long long db1 = (d * a3 + b3) % M;
            long long db2 = (d * a4 + b4) % M;
            d = (bessie[i] == 'T') ? db1 : db2;
        }
    }
    cout << answer << "\n";
    return 0;
}
