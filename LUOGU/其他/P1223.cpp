#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
struct Person { int id, t; };
bool cmp(const Person& a, const Person& b) { return a.t < b.t; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Person p[1001];
    for (int i = 0; i < n; i++) { cin >> p[i].t; p[i].id = i + 1; }
    sort(p, p + n, cmp);
    for (int i = 0; i < n; i++) { if (i) cout << " "; cout << p[i].id; }
    cout << "\n";
    double ans = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) { sum += p[i].t; ans += sum; }
    printf("%.2f\n", ans / n);
    return 0;
}
