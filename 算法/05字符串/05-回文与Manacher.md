前置：[[01-字符串基础与暴力匹配]]、[[05-双指针与滑动窗口]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 双指针回文判断 | 2/10 | 9/10 | 判断整个串，不必先学复杂模板 |
| 中心扩展 | 3/10 | 8/10 | 奇偶中心是 Manacher 的前置，也适合小数据 |
| Manacher | 6/10 | 7/10 | 复用对称半径，长串回文问题按需掌握 |

评分为本项目主观学习建议，尺度见 [[00-字符串]]。


## 先区分问整个串，还是问最长连续片段

回文从左向右和从右向左读相同。`abac` 整串不是回文，但最长回文子串为 aba、长度 3。只问整串时，两端指针逐对比较，$O(n)$ 已足够；最长回文子串才需要尝试多个中心。最长回文**子序列**允许跳过字符，是另一个 DP 问题，本章不解决。

## 双指针与中心扩展

整串判断只要每对镜像字符相同；空串、单字符按定义都是回文。最长子串枚举两类中心：奇数长度以 $s[i]$ 为中心，偶数长度以 $s[i]$ 和 $s[i+1]$ 的缝隙为中心。向两边同步延伸，遇到越界或不相等停止。

例：`cabbad`。中心选第 2、3 位的两个 b（0 下标），先比较 bb，再比较 aa，再遇到 $c\ne d$，得到 abba、长度 4。只枚举单字符中心会漏掉这个答案。

### 完整基础程序

输入一行字节字符串，可为空、可含空格，长度 $\le 5000$。先输出整串是否回文 Yes/No，再输出最长回文子串长度。判断 $O(n)$，中心扩展最坏 $O(n^{2})$，辅助空间 $O(1)$，输入占 $O(n)$；全 a 串让很多中心都扩展到边缘，正是最坏情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(const string &s)
{
    int left = 0;
    int right = (int)s.size() - 1;
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}

int expand_center(const string &s, int left, int right)
{
    int n = s.size();
    while (left >= 0 && right < n && s[left] == s[right])
    {
        --left;
        ++right;
    }
    return right - left - 1;
}

int longest_palindrome(const string &s)
{
    int answer = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        answer = max(answer, expand_center(s, i, i));
        answer = max(answer, expand_center(s, i, i + 1));
    }
    return answer;
}

int main()
{
    string s;
    getline(cin, s);
    cout << (is_palindrome(s) ? "Yes" : "No") << '\n';
    cout << longest_palindrome(s) << '\n';
}
```

教学样例输入（自编）：

```text
cabbad
```

输出：

```text
No
4
```

## Manacher：把已知回文的对称性用起来

概念上把 s 变成 `#s[0]#s[1]#…#`，长度 $N=2n+1$。原来的偶数回文也变成奇数，所有中心用一套半径处理。$\mathrm{radius}[i]$**包含中心**，最小为 1，覆盖闭区间 `[i−radius[i]+1,i+radius[i]−1]`；原串最长回文长度是 $\mathrm{radius}[i]-1$。

维护已处理回文中最靠右的一个：center 为中心、$\mathrm{right}=\mathrm{center}+\mathrm{radius}[\mathrm{center}]$ 为**右侧独占边界**，不是最右有效字符下标。实际最右字符是 $\mathrm{right}-1$，原笔记的“最右侧边界”用词在这里明确为半开边界，防止差 1。

当 $i<\mathrm{right}$，镜像 $\mathrm{mirror}=2center-i$ 已经求过半径；可安全继承 `min(radius[mirror],right−i)`。若镜像回文完全在已知大回文内部，可完整复用；若触及或超过已知范围，只能保证到 $\mathrm{right}-1$，范围外继续比较。$i\ge \mathrm{right}$ 时初始半径为 1，从头扩展。

## 手算镜像与边界

原串 `aba`，变成 `#a#b#a#`，下标 $0\ldots6$。中心 $i=3$ 的 b 向两边扩成整串，$\mathrm{radius}[3]=4$、$\mathrm{right}=7$。后来处理 $i=5$ 的 a，$\mathrm{mirror}=1$，已知 $\mathrm{radius}[1]=2$，所以初值 $\min (2,7-5)=2$，无需重比已知的 `#a#`。最大半径 4 对应原长度 3。

原串 `abba` 的虚拟分隔符中心 $i=4$ 半径为 5，原长度 4。同样的公式处理奇偶回文；不能把另一个教材中“不含中心的半径”公式直接混过来。

## 完整 Manacher 模板

输入一行，可为空、可含空格，长度 $\le 1.1\times 10^{7}$；输出最长回文子串长度。算法沿用原笔记的插分隔符、镜像复用机制，但不真的复制扩展字符串：偶数下标是虚拟分隔符，奇数下标取 $s[\mathrm{index}/2]$。这样原串含 `#` 也不会与虚拟分隔符混淆，省去一份 $O(n)$ 扩展串。

radius 用 vector 按长度分配，这是为匹配大输入的内存选择，未封装类。上限时半径数组约 88 MB、原串内容约 11 MB，还需考虑 string 的实际容量和运行环境；内存限制低于此规模时需要重新选择表示。[洛谷 P3805 — Manacher](https://www.luogu.com.cn/problem/P3805) 官方为非空小写串、同样最大长度，输出长度相同。

```cpp
#include <bits/stdc++.h>
using namespace std;

bool transformed_equal(const string &s, int left, int right)
{
    if ((left & 1) != (right & 1))
    {
        return false;
    }
    if ((left & 1) == 0)
    {
        return true;
    }
    return s[left / 2] == s[right / 2];
}

int manacher(const string &s)
{
    int size = (int)s.size() * 2 + 1;
    vector<int> radius(size, 0);
    int center = 0;
    int right = 0;
    int answer = 0;
    for (int i = 0; i < size; i++)
    {
        int length = 1;
        if (i < right)
        {
            int mirror = 2 * center - i;
            length = min(radius[mirror], right - i);
        }
        while (i - length >= 0 && i + length < size &&
            transformed_equal(s, i - length, i + length))
        {
            ++length;
        }
        radius[i] = length;
        if (i + length > right)
        {
            center = i;
            right = i + length;
        }
        answer = max(answer, length - 1);
    }
    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    getline(cin, s);
    cout << manacher(s) << '\n';
}
```

教学样例输入（自编）：

```text
abba
```

输出：

```text
4
```

## 为什么复用正确与边界安全

已知大回文内部镜像位置字符相同，因此镜像半径在大回文范围内的部分必然可搬到当前中心。范围外没有依据，只能显式扩展。扩展结束后 radius 是恰好最长的半径；只在更靠右时更新维护区间。mirror 在 $i<\mathrm{right}$ 的条件下处于有效已处理位置，因为维护的回文左边界没有越过字符串开头。

循环先检查两端合法再读取字符；没有使用未经边界检查的“哨兵 while”。空串对应一个虚拟分隔符，最长长度为 0。辅助空间 $O(n)$，总时间 $O(n)$，线性证明见最后。

已知各半径可恢复一条最长回文的 0 下标起点 `(i−radius[i]+1)/2`，长度 $\mathrm{radius}[i]-1$；回文子串总数（按不同出现位置计）为 `sum(radius[i]/2)`，每个中心只计与原串长度奇偶相符的扩展层，计数用 long long。


## 练习与复盘

先手算正文样例，再运行并检查最小输入、重复字符与边界；分层题目见 [[10-字符串题单]]，独立建模见 [[11-字符串综合练习]]。

## 扩展选读：不是每次扩展都会推进全局右边界

原笔记“每次匹配成功都会让 r 增大”说得过强：当 $i\ge \mathrm{right}$ 时，中心附近的扩展可能先填到旧边界；全局 right 也只在这个中心计算结束后更新。正确的摊还分析是：镜像回文严格位于维护区间内时，不会产生越过已知半径的成功比较；贴着边界或区间外时，新成功比较把候选边界向右扩展。新中心开始时的候选边界至少达到旧 right（区间外中心也在 right 右侧），因此这种额外成功扩展可记到不回退的 right 上，累计 $O(N)$；每中心至多一次失败比较，累计 $O(N)$。故总 $O(N)=O(n)$。

## CF2227D Palindromex

[官方题面](https://codeforces.com/contest/2227/problem/D)

数组长2N，0..N−1各出现两次，求所有回文连续子数组中最大的mex。

> [!tip]- 提示一
> 最优mex至少1，因此只需考虑含0的回文；0仅出现两次。

> [!tip]- 提示二
> 含一个0时它只能居中；含两个0时它们必须关于中心对称，候选中心至多三个。
>
> 复习：[[05字符串/05-回文与Manacher]]。

> [!example]- 详细题解
> **建模与源码主线。** 源码找0的位置p1,p2，分别从p1、p2的奇中心向外扩展；第三次取它们中点，奇数长度由同一中心开始、偶数长度由相邻两中心开始。各次只在两端值相等时扩展，用m记录出现值，最后从0扫描首个未出现者，取三者最大。
>
> **正确性与适用条件。** 回文中若某个0不在中心，其镜像也必须为0；因只有两次，含一个0必居中、含两个必为镜像，三种情况穷尽。固定中心扩得更长只会增加出现集合，mex不会下降，故仅需考察该中心的最大回文。
>
> **手算与边界。** a=(0,1,0,1)：以位置2为中心的(0,1,0)含0和1，mex=2；该中心正是两个0的中点。只检查以0本身为中心会漏掉答案。
>
> **实际复杂度与实现。** 三个中心各O(N)扩展与mex扫描，总O(N)，空间O(N)。每次必须清空出现标记；该三中心性质依赖每个值恰出现两次，不能直接推广到任意数组。

返回：[[00-字符串]]。
