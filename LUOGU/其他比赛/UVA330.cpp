#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Record {
    string name;
    int buy_price;
    int sell_price;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cmd;
    map<string, int> inventory;
    vector<Record> sold;
    int total_profit = 0;

    while (cin >> cmd && cmd != "#") {
        if (cmd == "BUY") {
            string name; int price;
            cin >> name >> price;
            inventory[name] = price;
        } else if (cmd == "SELL") {
            string name; int price;
            cin >> name >> price;
            if (inventory.count(name)) {
                int profit = price - inventory[name];
                sold.push_back({name, inventory[name], price});
                total_profit += profit;
                inventory.erase(name);
            }
        } else if (cmd == "LIST") {
            for (auto& p : inventory) {
                cout << p.first << "\n";
            }
        }
    }

    cout << "--- PROFIT ---\n";
    for (auto& r : sold) {
        cout << r.name << " " << (r.sell_price - r.buy_price) << "\n";
    }
    cout << "--- TOTAL ---\n";
    cout << total_profit << "\n";

    return 0;
}
