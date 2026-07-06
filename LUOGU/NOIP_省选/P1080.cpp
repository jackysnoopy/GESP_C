#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Person {
    int l, r;
};

// 高精度乘int
void mul(vector<int>& a, int b) {
    int carry = 0;
    for (int& x : a) {
        carry += x * b;
        x = carry % 10;
        carry /= 10;
    }
    while (carry) {
        a.push_back(carry % 10);
        carry /= 10;
    }
}

// 高精度除int
vector<int> div(const vector<int>& a, int b) {
    vector<int> res;
    int remain = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        remain = remain * 10 + a[i];
        res.push_back(remain / b);
        remain %= b;
    }
    reverse(res.begin(), res.end());
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

bool greater_vec(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = (int)a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] > b[i];
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Person> p(n + 1);
    for (int i = 0; i <= n; i++)
        cin >> p[i].l >> p[i].r;
    
    sort(p.begin() + 1, p.end(), [](const Person& a, const Person& b) {
        return a.l * a.r < b.l * b.r;
    });
    
    vector<int> prod = {1};
    vector<int> ans = {0};
    
    for (int i = 0; i <= n; i++) {
        if (i > 0) {
            vector<int> cur = div(prod, p[i].r);
            if (greater_vec(cur, ans)) ans = cur;
        }
        mul(prod, p[i].l);
    }
    
    for (int i = (int)ans.size() - 1; i >= 0; i--)
        cout << ans[i];
    cout << endl;
    
    return 0;
}