前置：[[02-图的存储]]、[[07-Bellman-Ford与SPFA]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| Floyd-Warshall | 5/10 | 8/10 | 点对动态规划，循环顺序是核心 |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 为什么要一次求出所有点对

若 n 小而询问多，每次查询都从头搜索会重复计算。Floyd 直接维护 $\mathrm{dist}[i][j]$，一次预处理后每对点 $O(1)$ 查询。n 很大时 $O(n^{3})$ 不可行，非负稀疏图可以对每个源运行 Dijkstra。

## 状态从允许的中转点推导

阶段 k 表示只允许编号 $1\ldots k$ 的点作为路径内部中转。最优路线要么不经过 k，要么由 i→k 和 k→j 两段拼成，所以 `dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j])`。k 必须在最外层，保证全部点对都使用同一阶段；把 i 放外层的单次扫描没有这个保证。

例：有 `1→2(4),2→3(−1),1→3(10)`。初始 $\mathrm{dist}[1][3]=10$；$k=2$ 时候选是 $4-1=3$，更新为 3。有负边但无负环时依然成立。零长度路径让对角线为 0；负自环应通过 min 保留而不能被后来的初始化抹掉。

## 完整教学模板

输入有向图 `n m` 与 m 条 `u v w`，输出 $n\times n$ 距离矩阵，不可达 −1。`n<=300,m<=200000,|w|<=10^9`，**保证无负环**；重边取最小值，未连通的两段不相加。模板不对负环图输出有限最短路，避免负环下反复放大负值及数值溢出。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300 + 5;
const long long INF = (1LL << 60);
long long dista[MAXN][MAXN];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dista[i][j] = (i == j ? 0 : INF);
        }
    }
    for (int e = 0; e < m; e++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dista[u][v] = min(dista[u][v], w);
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dista[i][k] != INF && dista[k][j] != INF)
                {
                    dista[i][j] = min(dista[i][j], dista[i][k] + dista[k][j]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            long long answer = (dista[i][j] == INF ? -1 : dista[i][j]);
            cout << answer << (j == n ? '\n' : ' ');
        }
    }
}
```

教学样例输入：

```text
3 3
1 2 4
2 3 -1
1 3 10
```

输出：

```text
0 4 3
-1 0 -1
-1 -1 0
```

## 正确性、复杂度与应用

对允许中转点的集合做阶段归纳：不经过 k 的最优路线由上一阶段保存；经过 k 的最优简单路线可以在 k 处切分。无负环时可选择简单最短路线，且 $\mathrm{dist}[k][k]=0$，使原地更新不会越过本阶段的语义。时间 $O(n^{3}+m)$，空间 $O(n^{2})$，之后每次查询 $O(1)$。

无向图读入时双向更新。可达性传递闭包用布尔矩阵与 `reach[i][j] |= reach[i][k] && reach[k][j]`；最小瓶颈路用 `min(current,max(left,right))`，不能不加解释地套用普通加法。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

## 扩展选读：负环影响与 Johnson

数学上 Floyd 后某个 $\mathrm{dist}[k][k]<0$ 表示负环；对 i 能到 k 且 k 能到 j 的点对，最短行走无下界，不能输出当前有限数值当答案。若要支持此功能，应另行限制数值或使用安全大整数并做受影响标记，本模板仅保证无负环。

Johnson 用 Bellman-Ford 得势能 h，再将边权改为 `w+h[u]−h[v]`，使其非负，之后多次 Dijkstra 并还原距离。它是稀疏图带负边的全源方案，属于后续选学，不能把大规模 Johnson 题当作 Floyd 的完整范围测试。


返回：[[00-图论]]。
