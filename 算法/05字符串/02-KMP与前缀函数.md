前置：[[01-字符串基础与暴力匹配]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 前缀函数 | 5/10 | 9/10 | border 与失配回退的统一状态 |
| KMP 单模式匹配 | 5/10 | 10/10 | 线性且确定，不依赖哈希碰撞假设 |

评分为本项目主观学习建议，尺度见 [[00-字符串]]。


## 已经相同的部分为什么不必再比

暴力失败时把模式重新对齐到下一个起点，从头比较。若已匹配部分的结尾与模式开头相同，就可以保留这段匹配，继续比较当前失败字符。KMP 用模式自身的前后缀关系寻找所有仍可能成功的对齐，文本扫描位置始终向右。

单模式找全部位置、重复前后缀、周期是它的典型应用；多模式直接逐个跑 KMP 会重复扫描文本，可在掌握 Trie 后看可选的 AC 自动机。

## 统一前缀函数 pi，避免两种 next 混用

pi[i] 表示 pattern[0..i] 的最长 border 长度，pi[0]=0。这不是“包含整个串的最长相同前后段”，长度必须小于 i+1。状态 j 是已匹配字符数，下一次比较的字符是 pattern[j]。

原笔记代码采用另一种 −1 哨兵 next：next[0]=−1，对 j>0 有 next[j]=pi[j−1]。它描述 **pattern[0..j−1]**，不是 pattern[0..j]。原正文把这两个定义混在一起；本篇完整模板统一 pi，不同时使用两套失配公式。

## 一步步求 pi

模式 `ABABAC`：

| i | 当前前缀 | pi[i] | 如何得到 |
|---:|---|---:|---|
| 0 | A | 0 | 单字符没有非空 border |
| 1 | AB | 0 | B 与开头 A 不同 |
| 2 | ABA | 1 | A 匹配第 0 位 |
| 3 | ABAB | 2 | 在长度 1 基础上追加 B |
| 4 | ABABA | 3 | 追加 A，border 为 ABA |
| 5 | ABABAC | 0 | C 不匹配 B；j 从 3→1→0，仍不匹配 A |

假设上一前缀的最长 border 为 j，下一个字符不匹配时，候选必须是该 border 自身的 border，所以 j=pi[j−1]；重复沿链退到更短候选，直到能延长或归零。不是 j−− 逐个尝试所有长度。

## 文本匹配与重叠出现

每步 text[i] 与 pattern[j] 比较，失配只退 j，不回退 i；成功 j 加 1。j=m 时完成一次，0 下标起点为 i−m+1，输出 1 下标需再加 1。随后退到 pi[m−1]，保留模式本身的 border，以便发现重叠。

文本 `ABABA`，模式 `ABA`：前 3 字符成功，输出 1；j 回到 1，已有后缀 A；再读 B、A，输出 3。若 j 清零，会漏掉后一次。

## 完整模板

输入两行：文本长度 0..10^6，模式长度 1..10^6；教学版 getline 可处理空格，但仍按字节比较。输出每次出现的 **1 下标**起点，各一行，最后输出 pi 数组。接口与 [洛谷 P3375 — KMP](https://www.luogu.com.cn/problem/P3375) 对应；官方输入非空且为大写字母，教学样例不是官方样例。程序要求模式非空。

build_prefix 构建模式信息；print_matches 扫描文本并即时输出，因此不额外存全部位置。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int pi[MAXN];

void build_prefix(const string &pattern)
{
    int m = pattern.size();
    pi[0] = 0;
    for (int i = 1; i < m; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            ++j;
        }
        pi[i] = j;
    }
}

void print_matches(const string &text, const string &pattern)
{
    int m = pattern.size();
    int j = 0;
    for (int i = 0; i < (int)text.size(); i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j])
        {
            ++j;
        }
        if (j == m)
        {
            cout << i - m + 2 << '\n';
            j = pi[j - 1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    build_prefix(pattern);
    print_matches(text, pattern);
    for (int i = 0; i < (int)pattern.size(); i++)
    {
        cout << pi[i] << (i + 1 == (int)pattern.size() ? '\n' : ' ');
    }
}
```

教学样例输入（自编）：

```text
ABABA
ABA
```

输出：

```text
1
3
0 0 1
```

## 为什么不会跳过正确匹配

失败前的匹配后缀若要作为新的模式前缀，必定是已匹配模式段的一个 border。pi 链按长度从大到小枚举所有这样的候选，只跳过不可能的对齐。成功保留的 j 字符仍与当前文本后缀完全相同，所以状态始终正确。

前缀函数 O(m)、扫描 O(n)，总时间 O(n+m)，辅助空间 O(m)；输入文本和模式另占 O(n+m)。静态数组按容量实际分配。单字符、模式比文本长、全部相同字符、无匹配、重叠匹配都应检查。

## 原有 −1 哨兵写法：局部兼容片段

如需复习原模板，先调用上述 build_prefix，非空模式长度 m<=10^6，再用下式构建同义的 fallback。失配时 j>0 用 fallback[j]；j=0 失败时文本前进，不把 −1 当作 string 下标。完整匹配 j=m 若要继续搜，应使用 pi[m−1]，不要访问只开到 m−1 的 fallback[m]。

```cpp
int fallback[MAXN];

void build_fallback(int m)
{
    fallback[0] = -1;
    for (int j = 1; j < m; j++)
    {
        fallback[j] = pi[j - 1];
    }
}
```


## 练习与复盘

先手算正文样例，再运行并检查最小输入、重复字符与边界；分层题目见 [[10-字符串题单]]，独立建模见 [[11-字符串综合练习]]。

## 扩展选读：线性复杂度与周期

扫描中 j 每成功一步至多增加 1，总增加量不超过 n；每次 while 回退严格减少 j，而 j 从不为负，所以总回退次数 O(n)。前缀构造同理，以 m 为上界；并不是“每个字符最多比较一次”，而是比较总数线性。

非空串长度 n、最后 border 长度 b，d=n−b 是最短的“允许末尾不完整”的周期：对所有 i>=d 有 s[i]=s[i−d]。完整重复块还需要 n%d=0，否则完整拼接的最短块只能取整串。详细推导与完整应用程序见字符串建模题解章。


返回：[[00-字符串]]。
