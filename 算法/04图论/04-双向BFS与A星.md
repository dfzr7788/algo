前置：[[03-DFS与BFS]]、[[04-堆与优先级队列]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 双向 BFS | 5/10 | 6/10 | 单对最短路的搜索方向和停止条件需证明 |
| A* | 6/10 | 5/10 | 效果依赖启发函数，通用最坏界没有优势 |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 为什么尝试减少搜索范围

BFS 从源点扩展到深度 d 时，若每层分支约为 b，树状状态空间可能探索约 $b^{d}$ 个状态。双向 BFS 从起终点各走一部分，希望将规模降到约 $b^{d/2}$；这是特定分支模型下的直觉，不是任意图的复杂度保证。A* 则利用“当前位置到目标至少还要花多少代价”优先探索更有希望的状态。

这两种方法都面向单个源点和单个目标。需要源点到全部顶点的距离时，普通 BFS 或 Dijkstra 更直接。

## 双向 BFS 的状态与停止条件

保存 ds、dt 两套距离和两个前沿队列，每轮只扩展某一侧的完整一层，通常选较小前沿。不要交替随意弹一个点并在首次碰撞后结束，这会打乱完整层的论证。下面先记录一层所有碰撞候选，取最小值，然后停止。

在无向链 `1—2—3—4—5` 上，两侧已发现距离 1 的球分别是 `\{1,2\}` 和 `\{5,4\}`。再扩展源侧整层 2，发现 3；下一次双方相接时拼接 $ds+dt$，得到 4。碰撞既可能发生在同一个点，也可能发生在一条连接两侧的边。

对有向图，从源点沿正向边搜索，从目标沿反向边搜索；否则得到的可能是目标“能到哪里”，而非“谁能到目标”。本模板只处理无向图。

输入 `n m s t` 和 m 条无向边，输出最少边数，不可达 −1。`n,m<=200000`，点 $1\ldots n$。expand_layer 固定本轮队列长度，避免新发现点继续在本轮扩展。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int ds[MAXN], dt[MAXN];

int expand_layer(queue<int> &q, int a[], int b[])
{
    int count = q.size();
    int best = INT_MAX;
    while (count--)
    {
        int u = q.front();
        q.pop();
        if (b[u] != -1)
        {
            best = min(best, a[u] + b[u]);
        }
        for (int v : g[u])
        {
            if (a[v] == -1)
            {
                a[v] = a[u] + 1;
                q.push(v);
            }
            if (b[v] != -1)
            {
                best = min(best, a[u] + 1 + b[v]);
            }
        }
    }
    return best;
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    fill(ds, ds + n + 1, -1);
    fill(dt, dt + n + 1, -1);
    queue<int> qs, qt;
    ds[s] = 0;
    dt[t] = 0;
    qs.push(s);
    qt.push(t);
    if (s == t)
    {
        cout << 0 << '\n';
        return 0;
    }
    while (!qs.empty() && !qt.empty())
    {
        int answer;
        if (qs.size() <= qt.size())
        {
            answer = expand_layer(qs, ds, dt);
        }
        else
        {
            answer = expand_layer(qt, dt, ds);
        }
        if (answer != INT_MAX)
        {
            cout << answer << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
```

教学样例输入：

```text
5 4 1 5
1 2
2 3
3 4
4 5
```

输出：

```text
4
```

### 为什么完整层相遇可以结束

两侧已发现集合都是各自起点的完整距离球。假设扩展前半径为 a、b 且没有相遇，那么长度不超过 $a+b$ 的路径都会有一个点同时属于两球，与没有相遇矛盾。一次扩展只增加一侧半径 1；若此时产生连接候选，候选长度达到此前排除的下界，且该层取最小候选。因此不会漏掉更短路线。整个过程时间 $O(n+m)$，总空间 $O(n+m)$。最坏情况下仍需访问整图。

## A*：已经花费 g，估计剩余 h

按 `f=g+h` 的小根堆取点。g 是实际已找到的距离，h 是剩余代价的估计下界。可采纳性指 h 不超过真实剩余距离，且目标 $h=0$；一致性要求每条边满足 `h(u)<=w(u,v)+h(v)`。一致性让 f 沿路径不下降，像 Dijkstra 一样可在目标第一次有效出堆时结束。

四方向、每步代价 1 的网格取曼哈顿距离 `|x−tx|+|y−ty|`：忽略障碍只会让路线更短，所以是下界；相邻一步只改变它至多 1，所以一致。允许斜走、传送或低代价跳跃后，该估值可能失效，必须重新证明。

例：$3\times 3$ 网格中心障碍，从 $(1,1)$ 到 $(3,3)$，初始 $g=0,h=4$；向右后 $g=1,h=3$，f 仍为 4；障碍使部分路线不可走，但最短路仍为 4。$h=0$ 时退化为 Dijkstra。不能把 h 放大后仍声称最短路保证成立。

### 完整网格模板

输入 n m、n 行由 `.` 和 `#` 构成的网格，再输入 `sx sy tx ty`（1 下标）。`1<=n,m<=500`，只允许四方向一步，输出最少步数，不可达 −1。程序内坐标改为 0 下标；检查起终点障碍；堆记录 g 并跳过过期项。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int INF = 1000000000;
string board[MAXN];
int dista[MAXN][MAXN];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int tx, ty;

int heuristic(int x, int y)
{
    return abs(x - tx) + abs(y - ty);
}

int main()
{
    int n, m, sx, sy;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> board[i];
        fill(dista[i], dista[i] + m, INF);
    }
    cin >> sx >> sy >> tx >> ty;
    --sx;
    --sy;
    --tx;
    --ty;
    if (board[sx][sy] == '#' || board[tx][ty] == '#')
    {
        cout << -1 << '\n';
        return 0;
    }
    // 元组依次保存 f、g、横坐标、纵坐标。
    priority_queue<tuple<int, int, int, int>,
        vector<tuple<int, int, int, int>>,
        greater<tuple<int, int, int, int>>> pq;
    dista[sx][sy] = 0;
    pq.push({heuristic(sx, sy), 0, sx, sy});
    while (!pq.empty())
    {
        auto [f, cost, x, y] = pq.top();
        pq.pop();
        if (cost != dista[x][y])
        {
            continue;
        }
        if (x == tx && y == ty)
        {
            cout << cost << '\n';
            return 0;
        }
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            if (board[nx][ny] == '#')
            {
                continue;
            }
            if (cost + 1 < dista[nx][ny])
            {
                dista[nx][ny] = cost + 1;
                pq.push({cost + 1 + heuristic(nx, ny), cost + 1, nx, ny});
            }
        }
    }
    cout << -1 << '\n';
}
```

教学样例输入：

```text
3 3
...
.#.
...
1 1 3 3
```

输出：

```text
4
```

本模板的一致启发函数保证每个状态有效扩展一次；$V=nm$、$E\le 4V$，时间 $O(V \log V)$，总空间 $O(V)$。效果取决于障碍和目标，不能保证比 BFS 更快。一般图若允许任意可采纳但不一致的 h，需允许重开状态，复杂度不能直接套用这个网格结论。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

返回：[[00-图论]]。
