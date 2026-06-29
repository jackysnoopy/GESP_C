# 337 个 _data.txt 中间文件处理计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development or superpowers:executing-plans to implement this plan task-by-task.

**Goal:** 为 337 个仅有 _data.txt 的洛谷题目生成 .cpp 和 .md 文件，归档到对应目录，更新 done.md，最后删除 _data.txt。

**Architecture:** 按难度从低到高分批处理（每批 5 题），读取 _data.txt 生成解题代码和题解，编译验证后归档。已知难度 5+ 题目跳过率约 60-70%，需接受高跳过率。

**Tech Stack:** C++11, Python3 (batch_fetch.py), g++ -std=c++11 -O2 -Wall -Wextra

---

## 现状分析

| 难度 | _data.txt 数量 | 已有 cpp | 待处理 |
|------|---------------|---------|--------|
| 0 | 1 | 0 | 1 |
| 5 | 171 | 14 | 157 |
| 6 | 131 | 1 | 130 |
| 7 | 49 | 0 | 49 |
| **合计** | **352** | **15** | **337** |

已有 cpp 的 15 个题目（难度 5）：P2102, P2215, P2511, P2748, P2751, P2874, P3051, P3076, P3112, P3129, P3132, P3141, P3602, P3606。这些需要生成 .md 并归档。

---

## Task 1: 为已有 cpp 的 15 个题目生成 .md 并归档

**Files:**
- Read: `七级/P{pid}.cpp` (已有)
- Create: `七级/P{pid}_{题名}.md`
- Modify: `done.md`

- [ ] **Step 1: 批量生成 .md 文件**

对 15 个已有 cpp 的题目，读取 cpp 代码，生成对应 .md 题解文件：

```bash
python3 << 'PYEOF'
import os, re

problems = {
    "P2102": "地砖铺设", "P2215": "上升序列", "P2511": "消灭病毒",
    "P2748": "音乐研究", "P2751": "安排活动", "P2874": "树形DP",
    "P3051": "矩阵填数", "P3076": "最大三角形", "P3112": "后缀表达式",
    "P3129": "标志设计", "P3132": "昆虫繁殖", "P3141": "标号计数",
    "P3602": "Koishi Loves Segments", "P3606": "Building a Tall Barn"
}

for pid, name in problems.items():
    cpp_path = f"七级/{pid}.cpp"
    if not os.path.exists(cpp_path):
        print(f"SKIP {pid}: no cpp")
        continue
    with open(cpp_path) as f:
        cpp = f.read()
    md = f"# {pid} {name}\n\n## 思路\n\n（从代码推断）\n\n## 代码\n\n```cpp\n{cpp}```\n"
    md_path = f"七级/{pid}_{name}.md"
    with open(md_path, 'w') as f:
        f.write(md)
    print(f"✓ {pid}_{name}.md")
PYEOF
```

- [ ] **Step 2: 更新 done.md**

为这 15 个题目添加 done.md 条目（如果尚未存在）。

- [ ] **Step 3: 删除对应 _data.txt**

```bash
rm -f P2102_data.txt P2215_data.txt P2511_data.txt P2748_data.txt P2751_data.txt \
      P2874_data.txt P3051_data.txt P3076_data.txt P3112_data.txt P3129_data.txt \
      P3132_data.txt P3141_data.txt P3602_data.txt P3606_data.txt
```

---

## Task 2: 处理难度 5 的 157 个题目

**策略：** 每批 5 题，读取 _data.txt → 生成 .cpp → 编译测试 → 生成 .md → 归档 → 更新 done.md → 删除 _data.txt。跳过太复杂的题目。

- [ ] **Step 1: 获取难度 5 题目列表**

```bash
ls *_data.txt | while read f; do
  pid=$(echo "$f" | sed 's/_data\.txt//')
  diff=$(grep "Difficulty:" "$f" | head -1 | grep -o '[0-9]' | head -1)
  if [ "$diff" = "5" ] && [ ! -f "${pid}.cpp" ]; then
    echo "$pid"
  fi
done
```

- [ ] **Step 2: 按批次处理（每批 5 题）**

对每个批次：
1. 读取 _data.txt 获取题目描述
2. 分析算法，生成 .cpp
3. 编译测试：`g++ -std=c++11 -O2 -Wall -Wextra -o /tmp/test 七级/{pid}.cpp`
4. 通过样例测试
5. 生成 .md 题解
6. 移动到 `七级/`
7. 更新 done.md
8. 删除 _data.txt

- [ ] **Step 3: 记录跳过的题目**

太复杂的题目记录到跳过列表，不生成代码。

---

## Task 3: 处理难度 6 的 130 个题目

**策略：** 同 Task 2，但预期跳过率更高（~80%）。

---

## Task 4: 处理难度 7 的 49 个题目

**策略：** 同 Task 2，但预期跳过率最高（~90%）。

---

## Task 5: 清理剩余 _data.txt

- [ ] **Step 1: 检查所有 _data.txt 状态**

```bash
ls *_data.txt | wc -l  # 应为 0
```

- [ ] **Step 2: 删除所有 _data.txt**

```bash
rm -f *_data.txt
```

---

## 预期结果

| 指标 | 预期值 |
|------|--------|
| 处理 _data.txt 总数 | 337 |
| 预计生成 cpp + md | ~80-120（难度 5 约 50-80，难度 6 约 20-30，难度 7 约 5-10） |
| 预计跳过 | ~220-260 |
| 最终 _data.txt 残留 | 0 |

## 执行建议

由于 337 个题目数量巨大，建议：
1. 先执行 Task 1（15 个已有 cpp 的补 md）
2. 然后按难度从低到高逐批处理
3. 每批完成后汇报进度
4. 接受高跳过率，不强求全部解出
