前置：[[01-状态设计与记忆化搜索]]。线性 DP 按序列位置推进，网格 DP 按坐标推进；关键都是找到依赖已完成状态的顺序。

## 用途与限制

从前面少数位置转移、安排每天的活动、只向右下移动的网格，都有天然阶段。若路径可以反复左右移动，坐标本身不再保证无环；若活动限制涉及更早的历史，就要扩充状态。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 线性递推 | 3/10 | 10/10 | 学习阶段与边界的最直接模型。 |
| 有限状态线性DP | 4/10 | 9/10 | 最后一次选择影响下一步时必须补维度。 |
| 网格DP | 4/10 | 9/10 | 二维依赖与滚动数组的重要入门。 |

评分为本学习路线的主观建议，尺度见 [[00-动态规划#评分尺度|评分尺度]]。

## 青蛙：前缀状态

`dp[i]` 为到达 i 的最小费用。`dp[1]=0`，从 $i-1$ 或 $i-2$ 来。高度 `10 30 40 20` 对应 `0 20 30 30`。这与上篇后缀记忆化的状态方向不同，最终答案相同。

完整程序：单组，`1<=n<=100000`，高度绝对值不超过 $10^{9}$，1 下标，$\mathrm{MAXN}=100005$，输出费用。与 [AtCoder DP A](https://atcoder.jp/contests/dp/tasks/dp_a) 同模型；教学范围另外允许 $n=1$ 和负高度。每个状态两条候选，时间与空间 $O(n)$。前驱只来自已求出的较小位置，按位置归纳正确。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
long long h[MAXN];
long long dp[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
    }
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + llabs(h[i] - h[i - 1]);
        if (i >= 3)
        {
            dp[i] = min(dp[i], dp[i - 2] + llabs(h[i] - h[i - 2]));
        }
    }
    cout << dp[n] << '\n';
}
```

教学输入（自设，非官方样例）：

```text
3
5 5 5
```

输出：

```text
0
```

## 每天三选一：为什么必须记住最后选择

有 n 天，每天选择 A/B/C 的一项，连续两天不能相同，收益可以相加。只留“前 i 天的最大收益”不够：最优前缀最后选 A 时，下一天就不能再选 A；略差但最后选 B 的前缀可能得到更优整体。

定义 `dp[i][j]` 为前 i 天、当天选 j 的最大收益。转移为上一天不同选择中的最大值加当天收益。首日直接填收益；不能把每日最大相加。教学例两天收益分别为 `(10,1,1)`、`(10,1,1)`，合法最优为 11，错误的逐日贪心给 20。

完整程序与 [AtCoder DP C — Vacation](https://atcoder.jp/contests/dp/tasks/dp_c) 同模型，单组，`1<=n<=100000`，每天三列收益，教学允许 `|收益|<=10^9`。输出必须每天选一项的最大总收益。用 prev_day 与 next_day 分离层，活动编号 $0\ldots2$；long long。时间 $O(n)$，额外空间 $O(1)$。最后活动划分互斥且穷尽，故可归纳证明转移。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long prev_day[3];
long long next_day[3];
long long value[3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int j = 0; j < 3; j++)
    {
        cin >> prev_day[j];
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> value[j];
        }
        for (int j = 0; j < 3; j++)
        {
            next_day[j] = max(prev_day[(j + 1) % 3], prev_day[(j + 2) % 3]) + value[j];
        }
        for (int j = 0; j < 3; j++)
        {
            prev_day[j] = next_day[j];
        }
    }
    cout << *max_element(prev_day, prev_day + 3) << '\n';
}
```

教学输入（自设，非官方样例）：

```text
2
10 1 1
10 1 1
```

输出：

```text
11
```

## 网格路径与滚动数组

从左上到右下，只能右移或下移，墙不能走。`dp[i][j]` 为到达格子的路径数；非墙来自上方与左方两类路径，墙处为 0，空起点为 1。按行从左到右填。

$2\times 3$ 网格 `... / .#.` 的二维表为 `1 1 1 / 1 0 1`，答案为 1。压成一行时，在处理 $(i,j)$ 前，`dp[j]` 仍是上行，`dp[j-1]` 已是本行；这正是所需版本。障碍处必须清零，不能保留上行值。

完整程序与 [AtCoder DP H — Grid 1](https://atcoder.jp/contests/dp/tasks/dp_h) 同模型。单组输入 H W 和 H 行字符，教学范围 `1<=H,W<=1000`，允许起终点为墙（答案为 0）。列 1 下标，字符 0 下标；$MOD=10^{9}+7$，$\mathrm{MAXW}=1005$，输出路径数取模。时间 $O(HW)$，额外空间 $O(W)$，包含当前读入行。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXW = 1000 + 5;
const long long MOD = 1000000007;
long long dp[MAXW];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h;
    int w;
    cin >> h >> w;
    for (int i = 1; i <= h; i++)
    {
        string row;
        cin >> row;
        for (int j = 1; j <= w; j++)
        {
            if (row[j - 1] == '#')
            {
                dp[j] = 0;
            }
            else if (i == 1 && j == 1)
            {
                dp[j] = 1;
            }
            else
            {
                dp[j] = (dp[j] + dp[j - 1]) % MOD;
            }
        }
    }
    cout << dp[w] << '\n';
}
```

教学输入（自设，非官方样例）：

```text
2 3
...
.#.
```

输出：

```text
1
```

## 常见错误与应用

一维变量不是天然正确的滚动数组，必须确认读到的是上一层还是本层。活动 DP 用两行避免相互覆盖；网格 DP 有意利用两种版本。最大子段和是“以 i 结尾”的另一个典型状态，详见 [[06-最大子段和]]，不要和“前 i 项的全局最优”混淆。DAG 上递推见 [[05-拓扑排序与DAG]]。

练习见 [[14-动态规划题单]]，试把青蛙改为最多跳 k 步，并分析 $O(nk)$ 是否够用。
