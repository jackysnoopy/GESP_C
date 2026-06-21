#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<ll> B(N + 1);
    for (int i = 1; i <= N; i++) cin >> B[i];
    vector<ll> P(N), U(N);
    for (int i = 1; i < N; i++) cin >> P[i];
    for (int i = 1; i < N; i++) cin >> U[i];

    ll total_people = 0, total_capacity = 0, total_umbrellas = 0;
    for (int i = 1; i < N; i++) total_people += P[i];
    for (int i = 1; i <= N; i++) total_capacity += B[i];
    for (int i = 1; i < N; i++) total_umbrellas += U[i];

    if (total_people > total_capacity + total_umbrellas) {
        cout << "NO\n";
        return 0;
    }

    vector<ll> rem_cap(N + 1);
    for (int i = 1; i <= N; i++) rem_cap[i] = B[i];

    ll total_cost = 0;
    vector<ll> left_go(N), umbrella_buy(N), right_go(N);

    for (int i = 1; i < N; i++) {
        ll people = P[i];
        ll to_left = min(people, rem_cap[i]);
        rem_cap[i] -= to_left;
        people -= to_left;
        left_go[i] = to_left;

        ll to_right = min(people, rem_cap[i + 1]);
        rem_cap[i + 1] -= to_right;
        people -= to_right;
        right_go[i] = to_right;

        ll umbrellas = min(people, U[i]);
        people -= umbrellas;
        umbrella_buy[i] = umbrellas;
        total_cost += umbrellas;

        if (people > 0) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    cout << total_cost << "\n";
    for (int i = 1; i < N; i++) {
        cout << left_go[i] << " " << umbrella_buy[i] << " " << right_go[i] << "\n";
    }
    return 0;
}
