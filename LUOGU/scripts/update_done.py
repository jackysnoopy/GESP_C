import os

done_file = 'done.md'
with open(done_file, 'r', encoding='utf-8') as f:
    lines = f.readlines()

# Find the index of "## 新增待处理题目 (共 40 题)"
start_index = -1
for i, line in enumerate(lines):
    if "新增待处理题目 (共 40 题)" in line:
        start_index = i
        break

if start_index != -1:
    # Keep everything before this section
    new_lines = lines[:start_index]
    
    # Add the new section once
    new_lines.append("\n## 新增待处理题目 (共 40 题)\n\n")
    new_lines.append("| 题号 | 题名 | 目录 | 状态 |\n")
    new_lines.append("| :--- | :--- | :--- | :--- |\n")
    
    # Add the 40 problems
    problems = [
        ("P11969", "「ALFR Round 7」T2 Game"),
        ("P12007", "【MX-X10-T3】[LSOT-4] 全国联赛？"),
        ("P12026", "[USACO25OPEN] Compatible Pairs S"),
        ("P12144", "[USACO25FEB] Moo Taste Test S"),
        ("P12148", "[USACO25FEB] Cow Weightlifting S"),
        ("P12187", "[USACO25FEB] Cow Steeplechase S"),
        ("P12234", "[蓝桥杯 2025 国 Java B] 重新排列"),
        ("P12275", "[蓝桥杯 2025 国 Python A] 平均分配"),
        ("P12283", "[蓝桥杯 2025 国 Python A] 优化路线"),
        ("P12302", "[蓝桥杯 2025 国 Java A] 密码破解"),
        ("P12331", "[蓝桥杯 2025 国 Python A] 压缩"),
        ("P12386", "[蓝桥杯 2025 国 Java A] 图像识别"),
        ("P12505", "[蓝桥杯 2024 国 Java B] 翻转"),
        ("P12652", "[蓝桥杯 2024 国 Python A] 路径"),
        ("P12668", "[蓝桥杯 2024 国 Java A] 货物摆放"),
        ("P12675", "[蓝桥杯 2024 国 Java A] 奇数偶数"),
        ("P12690", "[蓝桥杯 2024 国 Python A] 找数"),
        ("P12872", "[USACO25JAN] Cow Segments S"),
        ("P12933", "[USACO25JAN] Target Practice S"),
        ("P12938", "[USACO25JAN] Cowmpetitive S"),
        ("P12990", "[蓝桥杯 2023 国 Python B] 接龙"),
        ("P12993", "[蓝桥杯 2023 国 Python B] 矩形"),
        ("P13008", "[蓝桥杯 2023 国 Java B] 扫雷"),
        ("P13009", "[蓝桥杯 2023 国 Python B] 全球变暖"),
        ("P13030", "[蓝桥杯 2023 国 Java B] 杨辉三角"),
        ("P13039", "[蓝桥杯 2023 国 Python B] 路径"),
        ("P13056", "[蓝桥杯 2023 国 Python A] 翻转"),
        ("P13112", "[蓝桥杯 2023 国 Java A] 互质"),
        ("P13139", "[蓝桥杯 2023 国 Python A] 单词分析"),
        ("P13163", "[蓝桥杯 2023 国 Java A] 翻转"),
        ("P13169", "[蓝桥杯 2023 国 Python A] 路径"),
        ("P13172", "[蓝桥杯 2023 国 Python A] 差分"),
        ("P13193", "[蓝桥杯 2022 国 Java B] 因数分解"),
        ("P13218", "[蓝桥杯 2022 国 Java B] 球"),
        ("P13219", "[蓝桥杯 2022 国 Python B] 碰撞"),
        ("P13223", "[蓝桥杯 2022 国 Java A] 剪纸"),
        ("P13225", "[蓝桥杯 2022 国 Java A] 路径"),
        ("P13246", "[蓝桥杯 2022 国 Python A] 回路"),
        ("P13279", "[蓝桥杯 2022 国 Java A] 排列"),
        ("P13286", "[蓝桥杯 2022 国 Python A] 路径"),
    ]
    
    for pid, name in problems:
        new_lines.append(f"| {pid} | {name} |  | 待完善题解 |\n")
        
    with open(done_file, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)
    print("Fixed done.md")
else:
    print("Section not found")
