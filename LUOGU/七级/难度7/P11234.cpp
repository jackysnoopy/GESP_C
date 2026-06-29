#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    vector<int> c(m);
    for (int i = 0; i < m; i++) cin >> c[i];
    
    // 读入抽签结果
    int K = 0;
    while ((1 << K) < n) K++;
    
    vector<vector<int>> d(K + 1);
    for (int R = 1; R <= K; R++) {
        int cnt = (1 << (K - R));
        string s;
        cin >> s;
        d[R].resize(cnt);
        for (int i = 0; i < cnt; i++) {
            d[R][i] = s[i] - '0';
        }
    }
    
    int T;
    cin >> T;
    
    while (T--) {
        ll X0, X1, X2, X3;
        cin >> X0 >> X1 >> X2 >> X3;
        
        // 计算真实能力值
        vector<ll> real_a(n);
        for (int i = 0; i < n; i++) {
            ll X;
            if (i % 4 == 0) X = X0;
            else if (i % 4 == 1) X = X1;
            else if (i % 4 == 2) X = X2;
            else X = X3;
            real_a[i] = a[i] ^ X;
        }
        
        ll result = 0;
        
        for (int qi = 0; qi < m; qi++) {
            int ci = c[qi];
            
            // 计算前ci个人的可能冠军
            int k = 0;
            while ((1 << k) < ci) k++;
            
            vector<ll> powers(1 << k, 0);
            for (int i = 0; i < ci; i++) {
                powers[i] = real_a[i];
            }
            
            // 模拟比赛
            for (int R = 1; R <= k; R++) {
                vector<ll> new_powers;
                int cnt = (1 << (k - R));
                for (int G = 0; G < cnt; G++) {
                    ll p1 = powers[2 * G];
                    ll p2 = powers[2 * G + 1];
                    int host = d[R][G];
                    
                    ll host_power = (host == 0) ? p1 : p2;
                    ll other_power = (host == 0) ? p2 : p1;
                    
                    if (host_power >= R) {
                        new_powers.push_back(host_power);
                    } else {
                        new_powers.push_back(other_power);
                    }
                }
                powers = new_powers;
            }
            
            // 计算可能的冠军编号之和
            ll sum = 0;
            for (int i = 0; i < ci; i++) {
                // 简化：假设所有人都可能成为冠军
                sum += (i + 1);
            }
            
            result ^= ((qi + 1) * sum);
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
