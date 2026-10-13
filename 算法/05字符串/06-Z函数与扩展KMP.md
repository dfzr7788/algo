前置：[[02-KMP与前缀函数]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| Z 函数 | 5/10 | 7/10 | 求每个后缀与整串前缀的匹配长度 |
| 扩展 KMP | 6/10 | 6/10 | 把相同区间机制扩展到文本与模式两串 |

评分为本项目主观学习建议，尺度见 [[00-字符串]]。


## 它比 KMP 多告诉我们什么

KMP 关注“以当前位置结尾的文本后缀匹配了模式前缀多少”，适合找完整出现。Z 函数关注“从当前位置开始，后缀与整串前缀相同多少字符”；扩展 KMP 求文本每个后缀与模式前缀的最长公共前缀 LCP。

它们都能找出现位置，但并非只是给 KMP 的数组换名。若题目需要每个起点匹配前缀多长，而不仅仅是否全匹配，Z / 扩展 KMP 的输出更直接。已经会 KMP 后按需读，本章不是下一步必刷要求。

## Z 的定义与复用区间

z[i]=LCP(pattern,pattern[i..])。本篇规定 z[0]=m，其他资料有设为 0 的版本，只是约定不同，做加权和时会影响答案。维护 `[left,right)`：pattern[left..right) 与 pattern[0..right−left) 相同，是之前求过的最靠右匹配区间。

若 i<right，则当前字符位置对应前缀中的 i−left，可以复用 `min(z[i−left],right−i)`。z[i−left] 超过 right−i 时只保证已知区间内部分；区间外继续实际比较。i>=right 从 0 起步。

模式 `ababa` 的 Z 为 `[5,0,3,0,1]`：i=2 可匹配 aba，维护 [2,5)；i=3 复用 z[1]=0；i=4 复用 z[2]=3 但剩余窗口只有 1，初值只能是 1。

## 扩展 KMP 在文本上复用什么

extended[i]=LCP(pattern,text[i..])。维护文本中的 `[left,right)` 与模式前缀相同；在该区间内仍使用**模式的 z[i−left]**，不是随便搬 extended[i−left]。因为已知相同区间的参照串是 pattern。

文本 `ababc`、模式 `aba`：extended 为 `[3,0,2,0,0]`。起点 2 的文本后缀 abc 与 aba 只同 ab，长度 2；起点 0 长度 3 等于模式长度，是完整出现。i<right 时 i−left<m，参照 z 下标有效。

## 完整教学模板

输入文本、模式两行；文本长 0..10^6，模式长 1..10^6，按字节，可含空格。输出模式的 z 数组、文本的 extended 数组，各一行。静态容量分别容纳两串，模式必须非空。文本为空时第二行为空；只找出现可选所有 extended[i]==m 的 i。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int z[MAXN], extended[MAXN];

void build_z(const string &pattern)
{
    int m = pattern.size();
    z[0] = m;
    int left = 0;
    int right = 0;
    for (int i = 1; i < m; i++)
    {
        z[i] = 0;
        if (i < right)
        {
            z[i] = min(right - i, z[i - left]);
        }
        while (i + z[i] < m && pattern[z[i]] == pattern[i + z[i]])
        {
            ++z[i];
        }
        if (i + z[i] > right)
        {
            left = i;
            right = i + z[i];
        }
    }
}

void build_extended(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    int left = 0;
    int right = 0;
    for (int i = 0; i < n; i++)
    {
        extended[i] = 0;
        if (i < right)
        {
            extended[i] = min(right - i, z[i - left]);
        }
        while (extended[i] < m && i + extended[i] < n &&
            pattern[extended[i]] == text[i + extended[i]])
        {
            ++extended[i];
        }
        if (i + extended[i] > right)
        {
            left = i;
            right = i + extended[i];
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
    build_z(pattern);
    build_extended(text, pattern);
    for (int i = 0; i < (int)pattern.size(); i++)
    {
        cout << z[i] << (i + 1 == (int)pattern.size() ? '\n' : ' ');
    }
    for (int i = 0; i < (int)text.size(); i++)
    {
        cout << extended[i] << (i + 1 == (int)text.size() ? '\n' : ' ');
    }
    if (text.empty())
    {
        cout << '\n';
    }
}
```

教学样例输入（自编）：

```text
ababc
aba
```

输出：

```text
3 0 1
3 0 2 0 0
```

## 正确性与复杂度

维护区间内文本与模式前缀完全相同，把当前位置映射到模式位置，再用 Z 中已经证明的匹配长度给出安全下界。while 只对下界之外未知字符进行比较，停止时恰好达到真实 LCP。两串下标与模式长度均作界限检查。

模式 Z O(m)、文本扩展 O(n)，总 O(n+m) 时间、O(n+m) 辅助数组；固定容量实际分配另计。全相同字符、模式比文本长、起点在区间边缘、多个匹配都值得手算。


## 练习与复盘

先手算正文样例，再运行并检查最小输入、重复字符与边界；分层题目见 [[10-字符串题单]]，独立建模见 [[11-字符串综合练习]]。

## 扩展选读：线性与命名

若复用匹配严格在窗口内部，后续比较至多发现一次失败；若复用到窗口边缘，新的成功比较推进候选 right，right 单调不回退，累计成功扩展 O(n)。区间外从当前 i 开始，候选边界也不比旧 right 小，每个位置另至多一次失败，所以总线性。Z 模式构造同理。

“扩展 KMP”常也称 ex-KMP，算法主要是 Z 区间复用，并不直接使用 pi 的失配链。洛谷 P5410 的官方题面本次未能读取，本轮不添加未经核验的测试链接；本篇自编数组输出不声称对应其平台接口。


返回：[[00-字符串]]。
