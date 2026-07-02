# UVA267 - Palindromes (回文)

> **注意**：本题在 UVA Online Judge 中的实际编号为 **UVA 401**（题目页面：problem=342）。"Palindromes" 是该题的标题。

## 题目描述

给定若干字符串，对每个字符串判断它属于以下哪种类型：

1. **回文串（Palindrome）**：正读和反读相同
2. **镜像串（Mirrored String）**：将字符串反转后，每个字符替换为其镜像字符，结果与原串相同
3. **镜像回文串（Mirrored Palindrome）**：同时满足以上两个条件
4. **都不是**：既不是回文串也不是镜像串

**镜像字符映射表**：

| 字符 | 镜像 | 字符 | 镜像 |
|------|------|------|------|
| A | A | 1 | 1 |
| E | 3 | 2 | S |
| H | H | 3 | E |
| I | I | 5 | Z |
| J | L | 8 | 8 |
| L | J | | |
| M | M | | |
| O | O | | |
| S | 2 | | |
| T | T | | |
| U | U | | |
| V | V | | |
| W | W | | |
| X | X | | |
| Y | Y | | |
| Z | 5 | | |

其他字符没有镜像映射。

## 输入格式

多组测试数据，每行一个字符串（长度不超过 19，仅包含大写字母和数字）。输入以文件结束（EOF）终止。

## 输出格式

对每个输入字符串，输出一行：
- `<string> -- is a mirrored palindrome.`（镜像回文串）
- `<string> -- is a palindrome.`（仅回文串）
- `<string> -- is a mirrored string.`（仅镜像串）
- `<string> -- is not a palindrome.`（都不是）

每组输出之间用空行分隔。

## 样例输入

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

## 样例输出

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
```

## 解题思路

1. **回文判断**：从字符串两端向中间逐字符比较，若全部相同则为回文串。

2. **镜像判断**：将字符串反转，对每个字符查表得到其镜像字符，若反转+镜像后的结果与原串完全相同，则为镜像串。具体步骤：
   - 设字符串长度为 `n`，对 `i = 0` 到 `n/2`：
   - 检查 `mirrorChar(s[n-1-i]) == s[i]`
   - 若全部满足，则为镜像串

3. **镜像字符映射**：用 `switch` 语句实现，将 15 个有镜像的字符映射到其镜像字符，其余字符返回空格（表示无镜像）。

4. **输出分类**：根据回文和镜像的布尔值组合，输出四种结果之一。注意每组输出之间需要一个空行。

## 时间复杂度

$O(L)$，其中 $L$ 为字符串长度。回文判断和镜像判断各需 $O(L)$。

## 空间复杂度

$O(1)$，仅使用常数额外空间。
