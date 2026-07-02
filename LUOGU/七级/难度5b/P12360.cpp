#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> p(n), b(n), a(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> a[i];
    
    vector<pair<long long, long long>> opponent(n);
    for (int i = 0; i < n; i++) {
        opponent[i] = {b[i], p[i]};
    }
    
    sort(opponent.begin(), opponent.end());
    sort(a.begin(), a.end());
    
    long long totalPrize = 0;
    for (int i = 0; i < n; i++) totalPrize += p[i];
    
    long long minNeeded = totalPrize / 2 + 1;
    
    auto canWin = [&](int k) -> bool {
        vector<long long> myPlayers = a;
        vector<pair<long long, long long>> opp = opponent;
        
        vector<pair<long long, long long>> oppKnown(opp.begin(), opp.begin() + k);
        vector<pair<long long, long long>> oppUnknown(opp.begin() + k, opp.end());
        
        sort(oppKnown.begin(), oppKnown.end());
        sort(oppUnknown.begin(), oppUnknown.end());
        
        long long myTotal = 0;
        long long oppTotal = 0;
        
        for (int i = 0; i < k; i++) {
            auto& [oppSkill, prize] = oppKnown[i];
            bool canWin = false;
            for (int j = 0; j < (int)myPlayers.size(); j++) {
                if (myPlayers[j] > oppSkill) {
                    canWin = true;
                    myTotal += prize;
                    myPlayers.erase(myPlayers.begin() + j);
                    break;
                }
            }
            if (!canWin) {
                oppTotal += prize;
            }
        }
        
        return myTotal > totalPrize - myTotal;
    };
    
    if (canWin(0)) {
        cout << 0 << "\n";
        return 0;
    }
    
    int lo = 1, hi = n, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (canWin(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
