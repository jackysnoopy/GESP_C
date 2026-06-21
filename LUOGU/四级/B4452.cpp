#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    int price, priority;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N;
    cin >> M >> N;
    
    vector<Item> items(N);
    for (int i = 0; i < N; i++)
        cin >> items[i].name >> items[i].price >> items[i].priority;
    
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        if (a.priority != b.priority) return a.priority < b.priority;
        if (a.price != b.price) return a.price < b.price;
        return a.name < b.name;
    });
    
    vector<string> bought;
    for (const auto& item : items) {
        if (M >= item.price) {
            M -= item.price;
            bought.push_back(item.name);
        }
    }
    
    sort(bought.begin(), bought.end());
    for (const auto& name : bought)
        cout << name << '\n';
    
    return 0;
}