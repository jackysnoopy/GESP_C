#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        // 解析输入：按逗号分隔
        vector<string> items;
        string item;
        for (char c : line) {
            if (c == ',') {
                // 去掉前导空格
                size_t start = item.find_first_not_of(' ');
                if (start != string::npos) {
                    items.push_back(item.substr(start));
                }
                item.clear();
            } else {
                item += c;
            }
        }
        // 处理最后一个元素
        if (!item.empty()) {
            size_t start = item.find_first_not_of(' ');
            if (start != string::npos) {
                items.push_back(item.substr(start));
            }
        }

        if (items.empty()) continue;

        // 分离数字和字符串，记录位置
        vector<double> nums;
        vector<string> strs;
        vector<bool> isNum(items.size());

        for (size_t i = 0; i < items.size(); i++) {
            string& s = items[i];
            bool is_number = true;
            for (char c : s) {
                if (!isdigit(c) && c != '.' && c != '-') {
                    is_number = false;
                    break;
                }
            }
            if (is_number && !s.empty()) {
                isNum[i] = true;
                nums.push_back(stod(s));
            } else {
                isNum[i] = false;
                strs.push_back(s);
            }
        }

        // 分别排序
        sort(nums.begin(), nums.end());
        sort(strs.begin(), strs.end());

        // 按原始模式合并
        size_t ni = 0, si = 0;
        for (size_t i = 0; i < items.size(); i++) {
            if (i > 0) cout << ", ";
            if (isNum[i]) {
                // 整数输出时去掉小数点
                double v = nums[ni++];
                if (v == (int)v) {
                    cout << (int)v;
                } else {
                    cout << v;
                }
            } else {
                cout << strs[si++];
            }
        }
        cout << endl;
    }
    return 0;
}
