#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int mn, mx;
};

struct Lotion {
    int spf, cnt;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int C, L;
    cin >> C >> L;
    
    vector<Cow> cows(C);
    for (int i = 0; i < C; i++)
        cin >> cows[i].mn >> cows[i].mx;
    
    vector<Lotion> lotions(L);
    for (int i = 0; i < L; i++)
        cin >> lotions[i].spf >> lotions[i].cnt;
    
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.mn > b.mn;
    });
    sort(lotions.begin(), lotions.end(), [](const Lotion& a, const Lotion& b) {
        return a.spf < b.spf;
    });
    
    int ans = 0;
    for (const auto& cow : cows) {
        for (auto& lotion : lotions) {
            if (lotion.cnt > 0 && lotion.spf >= cow.mn && lotion.spf <= cow.mx) {
                lotion.cnt--;
                ans++;
                break;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}