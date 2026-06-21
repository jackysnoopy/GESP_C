#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> pigInf, otherInf;
    for (int i = 0; i < n; i++) {
        string sp; int inf;
        cin >> sp >> inf;
        if (sp == "pig") pigInf.push_back(inf);
        else otherInf.push_back(inf);
    }
    sort(pigInf.rbegin(), pigInf.rend());
    sort(otherInf.begin(), otherInf.end());
    // Prefix sums of other
    vector<long long> pref(otherInf.size() + 1, 0);
    for (int i = 0; i < (int)otherInf.size(); i++)
        pref[i + 1] = pref[i] + otherInf[i];
    long long ans = 0;
    for (int pi = 0; pi < (int)pigInf.size(); pi++) {
        int pigVal = pigInf[pi];
        // All non-pigs with influence < pigVal
        int cnt = lower_bound(otherInf.begin(), otherInf.end(), pigVal) - otherInf.begin();
        long long total = pigVal + pref[cnt];
        ans = max(ans, total);
    }
    cout << ans << "\n";
    return 0;
}
