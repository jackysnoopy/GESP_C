#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double S, C, L, P0;
    int N;
    cin >> S >> C >> L >> P0 >> N;
    const int MAXN = 10;
    double dist[MAXN], price[MAXN];
    dist[0] = 0; price[0] = P0;
    for (int i = 1; i <= N; i++) cin >> dist[i] >> price[i];
    dist[N + 1] = S; price[N + 1] = 0;
    int total_stations = N + 2;
    for (int i = 0; i < total_stations - 1; i++) {
        if (dist[i + 1] - dist[i] > C * L) { cout << "No Solution" << "\n"; return 0; }
    }
    double total_cost = 0;
    double fuel = 0;
    int cur = 0;
    while (cur < total_stations - 1) {
        int range_limit = cur;
        while (range_limit + 1 < total_stations && dist[range_limit + 1] - dist[cur] <= C * L) range_limit++;
        int cheapest = cur;
        for (int i = cur + 1; i <= range_limit; i++) {
            if (price[i] < price[cheapest]) cheapest = i;
        }
        if (cheapest == cur) {
            double need = C - fuel;
            total_cost += need * price[cur];
            fuel = C;
        } else {
            double dist_needed = dist[cheapest] - dist[cur];
            double fuel_needed = dist_needed / L;
            if (fuel_needed > fuel) {
                double buy = fuel_needed - fuel;
                total_cost += buy * price[cur];
                fuel = fuel_needed;
            }
        }
        double dist_to_next = dist[cur + 1] - dist[cur];
        fuel -= dist_to_next / L;
        cur++;
    }
    printf("%.2f\n", total_cost);
    return 0;
}
