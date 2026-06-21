#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
    int h, w, id;
};

class BIT {
private:
    vector<int> tree;
public:
    BIT(int n) : tree(n + 2, 0) {}
    
    void add(int i, int x) {
        for (; i < (int)tree.size(); i += i & -i)
            tree[i] += x;
    }
    
    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += tree[i];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Person> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].h >> a[i].w;
        a[i].id = i;
    }
    
    sort(a.begin(), a.end(), [](const Person& x, const Person& y) {
        if (x.h != y.h) return x.h > y.h;
        if (x.w != y.w) return x.w > y.w;
        return x.id < y.id;
    });
    
    vector<int> rank(n);
    for (int i = 0; i < n; i++)
        rank[a[i].id] = i + 1;
    
    BIT bit(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += i - bit.sum(rank[i]);
        bit.add(rank[i], 1);
    }
    
    cout << ans << '\n';
    return 0;
}