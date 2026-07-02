#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <utility>
using namespace std;

typedef long long ll;

struct Fraction {
    ll num, den;
    Fraction(ll n = 0, ll d = 1) : num(n), den(d) {}
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
    bool operator>(const Fraction& other) const {
        return other < *this;
    }
    bool operator<=(const Fraction& other) const {
        return !(other < *this);
    }
    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }
};

struct State {
    Fraction time;
    int world;
    State(Fraction t, int w) : time(t), world(w) {}
    bool operator<(const State& other) const {
        return time > other.time;
    }
};

vector<ll> A, Q;
int N;

Fraction get_time(int u, int v) {
    if (u == v) return Fraction(0, 1);
    ll num = A[u] - A[v];
    ll den = u - v;
    if (den < 0) {
        num = -num;
        den = -den;
    }
    if (num < 0) return Fraction(-1, 1); // negative time, invalid
    return Fraction(num, den);
}

Fraction dijkstra(int start, int target) {
    vector<Fraction> dist(N+1, Fraction(1, 0)); // infinite
    dist[start] = Fraction(0, 1);
    priority_queue<State> pq;
    pq.push(State(Fraction(0, 1), start));
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (cur.time > dist[cur.world]) continue;
        if (cur.world == target) return cur.time;
        for (int v = 1; v <= N; ++v) {
            if (v == cur.world) continue;
            Fraction t = get_time(cur.world, v);
            if (t.num < 0) continue; // invalid
            if (t < cur.time) continue; // cannot jump before current time
            if (t < dist[v]) {
                dist[v] = t;
                pq.push(State(t, v));
            }
        }
    }
    return Fraction(-1, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    A.resize(N+1);
    Q.resize(N+1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> Q[i];
    for (int i = 1; i <= N; ++i) {
        if (i == Q[i]) {
            cout << "0/1\n";
            continue;
        }
        Fraction ans = dijkstra(i, Q[i]);
        if (ans.num < 0) cout << "-1\n";
        else cout << ans.num << "/" << ans.den << "\n";
    }
    return 0;
}