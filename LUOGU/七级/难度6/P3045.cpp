#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    long long m;
    cin >> n >> k >> m;
    
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    // Sort by coupon price
    sort(cows.begin(), cows.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    // Use priority queue for cows without coupons
    priority_queue<int> pq;
    
    long long total_cost = 0;
    int count = 0;
    
    // First, try to buy cows with coupons
    for (int i = 0; i < min(k, n); i++) {
        if (total_cost + cows[i].second <= m) {
            total_cost += cows[i].second;
            count++;
        } else {
            break;
        }
    }
    
    // Then, try to buy remaining cows with regular prices
    // Sort remaining cows by regular price
    vector<int> remaining;
    for (int i = k; i < n; i++) {
        remaining.push_back(cows[i].first);
    }
    sort(remaining.begin(), remaining.end());
    
    for (int price : remaining) {
        if (total_cost + price <= m) {
            total_cost += price;
            count++;
        } else {
            break;
        }
    }
    
    cout << count << "\n";
    return 0;
}
