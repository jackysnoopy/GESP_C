#include <iostream>
#include <algorithm>
using namespace std;

struct Person { int id, t; };

bool cmp(const Person& a, const Person& b) {
    if (a.t != b.t) return a.t < b.t;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Person p[1001];
    for (int i = 0; i < n; i++) {
        cin >> p[i].t;
        p[i].id = i + 1;
    }

    sort(p, p + n, cmp);

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << p[i].id;
    }
    cout << endl;

    double totalWait = 0;
    long long prefixSum = 0;
    for (int i = 0; i < n; i++) {
        totalWait += prefixSum;
        prefixSum += p[i].t;
    }

    printf("%.2f\n", totalWait / n);
    return 0;
}
