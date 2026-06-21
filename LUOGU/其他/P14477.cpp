#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string name;
    cin >> name;
    // Map province names to codes
    if (name == "北京") cout << 11 << endl;
    else if (name == "天津") cout << 12 << endl;
    else if (name == "河北") cout << 13 << endl;
    else if (name == "山西") cout << 14 << endl;
    else if (name == "内蒙古") cout << 15 << endl;
    else if (name == "辽宁") cout << 21 << endl;
    else if (name == "吉林") cout << 22 << endl;
    else if (name == "黑龙江") cout << 23 << endl;
    else if (name == "上海") cout << 31 << endl;
    else if (name == "江苏") cout << 32 << endl;
    else if (name == "浙江") cout << 33 << endl;
    else if (name == "安徽") cout << 34 << endl;
    else if (name == "福建") cout << 35 << endl;
    else if (name == "江西") cout << 36 << endl;
    else if (name == "山东") cout << 37 << endl;
    else if (name == "河南") cout << 41 << endl;
    else if (name == "湖北") cout << 42 << endl;
    else if (name == "湖南") cout << 43 << endl;
    else if (name == "广东") cout << 44 << endl;
    else if (name == "广西") cout << 45 << endl;
    else if (name == "海南") cout << 46 << endl;
    else if (name == "重庆") cout << 50 << endl;
    else if (name == "四川") cout << 51 << endl;
    else if (name == "贵州") cout << 52 << endl;
    else if (name == "云南") cout << 53 << endl;
    else if (name == "西藏") cout << 54 << endl;
    else if (name == "陕西") cout << 61 << endl;
    else if (name == "甘肃") cout << 62 << endl;
    else if (name == "青海") cout << 63 << endl;
    else if (name == "宁夏") cout << 64 << endl;
    else if (name == "新疆") cout << 65 << endl;
    else if (name == "台湾") cout << 71 << endl;
    else if (name == "香港") cout << 81 << endl;
    else if (name == "澳门") cout << 82 << endl;
    else cout << -1 << endl;
    return 0;
}
