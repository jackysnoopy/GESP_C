// UVA139 - Telephone Lines (电话线)
// 电话号码格式化
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

struct Record {
    std::string name;
    std::string number;
};

std::string formatNumber(const std::string& number) {
    if (number.empty()) return "";
    
    // 检查是否有区号（第一个字符不是+或数字）
    size_t i = 0;
    std::string areaCode;
    std::string localNum;
    
    if (number[0] == '+') {
        // 国际格式：+区号-本地号码
        i = 1;
        while (i < number.size() && number[i] != '-') {
            areaCode += number[i];
            i++;
        }
        if (i < number.size() && number[i] == '-') {
            i++;
        }
        while (i < number.size()) {
            localNum += number[i];
            i++;
        }
    } else if (number[0] == '(' && number.find(')') != std::string::npos) {
        // 括号格式：(区号)本地号码
        i = 1;
        while (i < number.size() && number[i] != ')') {
            areaCode += number[i];
            i++;
        }
        i++; // 跳过')'
        while (i < number.size()) {
            localNum += number[i];
            i++;
        }
    } else {
        // 检查是否是纯数字（本地号码）
        localNum = number;
    }
    
    // 格式化输出
    std::string result = "+";
    if (!areaCode.empty()) {
        result += areaCode + "-";
    }
    result += localNum;
    return result;
}

int main() {
    std::vector<Record> records;
    std::string line;
    
    while (std::getline(std::cin, line) && line != "#") {
        if (line.empty()) continue;
        
        size_t spacePos = line.find(' ');
        if (spacePos == std::string::npos) continue;
        
        Record rec;
        rec.name = line.substr(0, spacePos);
        rec.number = line.substr(spacePos + 1);
        
        // 过滤无效号码（长度不是7的本地号码）
        std::string digits;
        for (char c : rec.number) {
            if (std::isdigit(c)) {
                digits += c;
            }
        }
        
        // 如果本地号码长度不是7，跳过
        if (digits.length() == 7) {
            records.push_back(rec);
        }
    }
    
    // 按名字排序
    std::sort(records.begin(), records.end(), 
        [](const Record& a, const Record& b) {
            return a.name < b.name;
        });
    
    // 输出
    for (const auto& rec : records) {
        std::cout << rec.name << "," 
                  << formatNumber(rec.number) << std::endl;
    }
    
    return 0;
}
