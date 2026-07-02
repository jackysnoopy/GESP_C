#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string int_to_bin(int x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        s += (x % 2) ? '1' : '0';
        x /= 2;
    }
    reverse(s.begin(), s.end());
    return s;
}

// 比较两个二进制字符串拼接后的大小
bool cmp(const string& a, const string& b) {
    return a + b > b + a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<string> bins;
    for (int i = 1; i <= n; ++i) {
        bins.push_back(int_to_bin(i));
    }
    
    // 排序
    sort(bins.begin(), bins.end(), cmp);
    
    // 拼接二进制字符串
    string total_bin;
    for (const string& s : bins) {
        total_bin += s;
    }
    
    // 将二进制字符串转换为十进制数（高精度）
    // 由于二进制串可能很长，我们需要用vector<int>存储十进制数的每一位
    vector<int> decimal;
    decimal.push_back(0);
    
    for (char c : total_bin) {
        // 乘以2
        int carry = 0;
        for (int i = 0; i < decimal.size(); ++i) {
            int val = decimal[i] * 2 + carry;
            decimal[i] = val % 10;
            carry = val / 10;
        }
        if (carry > 0) {
            decimal.push_back(carry);
        }
        // 加上当前位
        int add = c - '0';
        if (add > 0) {
            carry = add;
            for (int i = 0; i < decimal.size(); ++i) {
                int val = decimal[i] + carry;
                decimal[i] = val % 10;
                carry = val / 10;
                if (carry == 0) break;
            }
            if (carry > 0) {
                decimal.push_back(carry);
            }
        }
    }
    
    // 输出十进制数
    for (int i = decimal.size() - 1; i >= 0; --i) {
        cout << decimal[i];
    }
    cout << endl;
    
    return 0;
}