前置：[[03-尼姆博弈]]。SG（Sprague–Grundy）函数给每个局面一个非负整数，使复杂无偏游戏可以和其他独立游戏一起分析。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| SG 函数与独立和 | 6/10 | 9/10 | 是多子游戏分析的主线。 |
| 分裂游戏 SG 递推 | 6/10 | 6/10 | 训练一步产生多个子游戏的建模。 |

## 为什么胜负布尔值不够

单堆 Nim 的 1 和 2 都必胜，但 $(1,1)$ 必败，$(1,2)$ 必胜。因此“两个必胜游戏组合起来”没有固定结果，需要保留比 0/1 更丰富的信息。SG 值就是在独立和中可替代这局游戏的 Nim 堆大小；它不表示石子真实数量、剩余步数或胜率。

适用条件：双人、轮流、完全信息、无随机、同一状态双方操作相同、游戏必定有限、无法行动者输。独立和还要求每次只在一个子游戏中行动，且这次行动不改变其他子游戏的规则和状态。反常规则、计分目标、有环无限游戏不能直接套本篇结论。理论参考 [MIT — Theory of Impartial Games](https://ocw.mit.edu/courses/es-268-the-mathematics-in-toys-and-games-spring-2010/c3ca97eef538f484348fcc6909043228_MITES_268S10_Ses1_theory.pdf)。

## mex 与单局递推

$\operatorname{mex}(S)$ 为未出现在 S 中的最小非负整数。$\operatorname{mex}(\{1,2,3\})=0$，$\operatorname{mex}(\{0,1,3\})=2$，$\operatorname{mex}(\{0,0,1\})=2$，$\operatorname{mex}(\varnothing)=0$；重复后继值不影响结果。

$$
SG(x)=\operatorname{mex}\{SG(y):x\to y\}.
$$

终局为 0；$\operatorname{SG}(x)=0$ 等价于 P 态，非零等价于 N 态。因为 mex 为 0 表示所有后继均非零；mex 非零意味着存在值为 0 的后继。

若 $\operatorname{SG}(x)=k$，后继值不能等于 k，且必包含 $0\ldots k-1$，但**也可能含有大于 k 的值**。SG 不是每次严格下降的数。等价于 Nim 指组合游戏中的价值等价，不是操作图完全相同。

对于一堆普通 Nim，所有后继是 $0\ldots x-1$，由归纳得 $\operatorname{SG}(x)=x$。巴什的连续取数得到 $\operatorname{SG}(x)=x \bmod (m+1)$。

## 独立和为什么用异或

对独立游戏 $G1\ldots Gn$，每回合只动其中一个，有：

$$
SG(G_1+\cdots+G_n)=SG(G_1)\oplus\cdots\oplus SG(G_n).
$$

这里的加号表示游戏的独立和，不是石子数相加。总异或 $S=0$ 则必败，否则必胜。零态改变一个子游戏的 SG 值一定变成非零；非零态可找一个 g 使 `g xor S<g`，mex 性质保证有合法后继 SG 恰为 `g xor S`。所以存在走到零态的动作。

构造时先决定目标 SG，再枚举**实际合法动作**找该值，不能把 SG 差当成取石子数量。

## 手算原例：取 1、3、4

| x | 可达 SG 集合 | $\operatorname{SG}(x)$ |
|---:|---|---:|
| 0 | 空 | 0 |
| 1 | ${0}$ | 1 |
| 2 | ${1}$ | 0 |
| 3 | ${0}$ | 1 |
| 4 | $\{0,1\}$ | 2 |
| 5 | $\{0,1,2\}$ | 3 |

三堆 $(4,5,2)$ 对应 $(2,3,0)$，总异或 1。把数量 5 的堆取 1 变成 4，就得到 $(2,2,0)$，对手必败。原例中的这个操作有效，但没有先枚举实际后继就不应宣称制胜操作唯一：SG 后继可以大于当前值。

## 完整程序：多个独立的集合取数游戏

自编格式：第一行 m、n（取数种类和堆数），第二行 m 个正取数，第三行 n 个非负堆数。$1\le m\le 100$，$1\le n\le 100000$，堆数 $\le 100000$，取数 $\le 100000$。每次选一堆取合法数量，无法行动者输。只输出 First/Second，不输出首步。

`build_sg` 递推所有 0..最大堆数；`seen` 每个状态重置。一个状态最多 m 种后继，所以 $\operatorname{mex}\le m$；大小 $m+1$ 足以标记全部相关值。moves、heap 为 0 下标。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXX = 100000 + 5;
const int MAXM = 100 + 5;
int moves[MAXM];
int heap[MAXX];
int sg[MAXX];
bool seen[MAXM];

void build_sg(int m, int limit)
{
    sg[0] = 0;
    for (int x = 1; x <= limit; x++)
    {
        fill(seen, seen + m + 1, false);
        for (int i = 0; i < m; i++)
        {
            if (moves[i] <= x)
            {
                seen[sg[x - moves[i]]] = true;
            }
        }
        int value = 0;
        while (seen[value])
        {
            value++;
        }
        sg[x] = value;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        cin >> moves[i];
    }
    int limit = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> heap[i];
        limit = max(limit, heap[i]);
    }
    build_sg(m, limit);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum ^= sg[heap[i]];
    }
    cout << (sum != 0 ? "First" : "Second") << '\n';
    return 0;
}
```

样例输入三行 `3 3`、`1 3 4`、`4 5 2`，输出 First。复杂度 $O(mA+n)$，A 为最大堆数；有效空间 $O(A+n+m)$，静态分配按声明容量。重复取数不影响结果但浪费时间；取数 0 会让状态依赖自身，必须拒绝。

## 一步分裂成两个子游戏

自编规则：每次选择一个正数堆 x，拆成两个**大小不同的正数堆** i 和 $x-i$。不能再拆者输；1、2 均不能拆。一次拆完后，这两堆是独立游戏，因此该动作的后继 SG 为 `sg[i] xor sg[x−i]`。所有动作之间再取 mex：

$$
SG(x)=\operatorname{mex}\{SG(i)\oplus SG(x-i):1\le i<x-i\}.
$$

先异或同一动作产生的子游戏，再对不同动作取 mex。不能把 `sg[i]` 与 `sg[x−i]` 分别丢进 mex。游戏有限，因为总石子数不变、每次堆数增加，而堆数最多达到总石子数。

## 完整程序：不等分拆堆

自编输入一行 n，$1\le n\le 500$，初始仅一堆；输出 First/Second。sg 保存 $1\ldots n$；每种动作只枚举较小一半，避免重复。后继异或可能大于 n，但每个状态动作数小于 n，所以 $\operatorname{mex}\le n$；大于 n 的值不影响 mex，直接忽略，seen 容量 505 足够。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 500 + 5;
int sg[MAXN];
bool seen[MAXN];

void build_split_sg(int n)
{
    for (int x = 1; x <= n; x++)
    {
        fill(seen, seen + n + 1, false);
        for (int left = 1; left < x - left; left++)
        {
            int value = sg[left] ^ sg[x - left];
            if (value <= n)
            {
                seen[value] = true;
            }
        }
        int value = 0;
        while (seen[value])
        {
            value++;
        }
        sg[x] = value;
    }
}

int main()
{
    int n;
    cin >> n;
    build_split_sg(n);
    cout << (sg[n] != 0 ? "First" : "Second") << '\n';
    return 0;
}
```

$n=3$ 只能拆 $1+2$，后继值 0，所以 $\operatorname{SG}(3)=1$，输出 First。$n=4$ 只能拆 $1+3$，后继值 1，所以 $\operatorname{SG}(4)=0$，输出 Second。时间 $O(n^{2})$，空间 $O(n)$。多初始堆需要读入堆数、预处理到最大值、异或各堆 SG；不能只异或初始堆大小。

## 常见限制与练习

威佐夫中同一步改两堆，不能将它们视为两个独立 Nim 游戏；斐波那契分解的数项也不自动成为独立子游戏。一个二维局面本身仍可作为一个完整游戏求 SG，问题在于错误拆分。

有限集合取数的 SG 最终周期可通过有限长度窗口递推证明存在，但只看前十几项不能断定周期从 0 开始。未知拆堆游戏不应直接套这个有限减法窗口结论。

练习见 [[11-博弈题单]] 的 S1、S2、ABC368 F；先完成独立和，再读 [[09-博弈建模与优化题解]] 的 SG 闭式推导。
