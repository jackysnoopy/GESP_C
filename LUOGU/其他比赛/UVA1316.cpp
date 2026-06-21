#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item { int profit, deadline; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<Item> items(n);
        int max_d = 0;
        for (int i = 0; i < n; i++) {
            cin >> items[i].profit >> items[i].deadline;
            max_d = max(max_d, items[i].deadline);
        }
        
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.profit > b.profit;
        });
        
        vector<int> parent(max_d + 2);
        for (int i = 0; i <= max_d + 1; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        int ans = 0;
        for (const auto& item : items) {
            int day = find(min(item.deadline, max_d));
            if (day > 0) {
                ans += item.profit;
                parent[day] = find(day - 1);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}