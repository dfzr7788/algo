前置：[[06-Dijkstra与非负权最短路]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| Bellman-Ford | 5/10 | 8/10 | 负边及负环判定有清晰轮数界 |
| SPFA | 6/10 | 5/10 | 队列优化需要理解，最坏情况仍慢 |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 有负边时为什么继续松弛

假设 `1→2(2),1→3(5),3→2(−10)`。先取 2 并不能确定答案，它还能通过 3 改成 −5。Bellman-Ford 放弃非负边的贪心，逐轮尝试所有边。松弛是“把到 u 的一条已知路线接上 u→v，若更短则更新 v”，不是直接把 $\mathrm{dist}[v]$ 设置为边权。

负环只影响从源点能到该环、再从该环能到达的目标；与源不连通的负环不影响单源距离。如果问题只问某个 t，源可达负环却无法到 t，t 的最短路仍可能有限。下面模板遇到任何源可达负环就统一报告，不逐点区分受影响状态。

## Bellman-Ford 的轮次状态

令第 k 轮 $\mathrm{dist}[v]$ 表示使用至多 k 条边到 v 的最小代价。每轮先备份 previous_dist，所有候选由上一轮产生；原 dist 保留“更少边”的候选。初始只有 $\mathrm{dist}[s]=0$。对上面的例子，第 1 轮 $\mathrm{dist}[2]=2$、$\mathrm{dist}[3]=5$；第 2 轮经 3 改为 −5。

没有可达负环时，最短路线可以删除非负环，选为至多 $n-1$ 条边的简单路径。若第 n 轮仍严格改进，就存在源可达负环。备份不是每个 Bellman-Ford 实现都必须，但“最多 k 条边”的明确题意必须备份；原地版本一轮可能传播多条边。

### 完整模板

输入 `n m s` 和有向边 `u v w`，`n<=5000,m<=20000,|w|<=10^9`，输出距离，不可达 −1；源可达负环输出 NEGATIVE CYCLE。−1 也可能是一个合法有限距离，教学输出仅表达数值；需要区分时可把不可达改成 INF 字符串。$O(n(n+m))$ 时间，通常称 $O(nm+n^{2})$；空间 $O(n+m)$。这里每轮备份 n 项，不把 $m=0$ 时的复制成本忽略。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 5;
const int MAXM = 20000 + 5;
const long long INF = (1LL << 60);
int from_node[MAXM], to_node[MAXM];
long long weight[MAXM], dista[MAXN], previous_dist[MAXN];

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int e = 0; e < m; e++)
    {
        cin >> from_node[e] >> to_node[e] >> weight[e];
    }
    fill(dista, dista + n + 1, INF);
    dista[s] = 0;
    for (int round = 1; round <= n; round++)
    {
        copy(dista, dista + n + 1, previous_dist);
        bool changed = false;
        for (int e = 0; e < m; e++)
        {
            int u = from_node[e];
            int v = to_node[e];
            if (previous_dist[u] != INF &&
                dista[v] > previous_dist[u] + weight[e])
            {
                dista[v] = previous_dist[u] + weight[e];
                changed = true;
            }
        }
        if (!changed)
        {
            break;
        }
        if (round == n)
        {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        long long answer = (dista[i] == INF ? -1 : dista[i]);
        cout << answer << (i == n ? '\n' : ' ');
    }
}
```

教学样例输入：

```text
3 3 1
1 2 2
1 3 5
3 2 -10
```

输出：

```text
0 -5 5
```

## SPFA：只处理发生改进的出发点

如果某轮 $\mathrm{dist}[u]$ 未变，重复扫描 u 的出边没有新候选。SPFA 用队列保存可能带来改进的点；in_queue 表示“当前已在队列”，出队后应清除，未来仍允许重新入队。它不是永久访问标记。

沿 `1→2(2),1→3(5),3→2(−10)`，1 先让 2、3 入队；2 处理结束后出队；3 再改进 2，2 需要重新进队。禁止第二次进队会漏掉传播。

负环检测用 $\mathrm{path\_edges}[v]=\mathrm{path\_edges}[u]+1$，记录本次严格改进路线的边数；达到 n 意味着其改进历史包含重复点。若重复段非负，则此前到该点的更短前缀已知，绕一圈不能产生严格改进，故这样的重复段必须含负环。这个计数不是“v 被松弛了几次”：多条平行边就可能让同一点在没有环时被松弛很多次。

### 完整模板

输入输出和容量同上一程序，处理单组数据。多测要清理 g、in_queue、path_edges 并重新初始化距离。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 5;
const long long INF = (1LL << 60);
vector<pair<int, long long>> g[MAXN];
long long dista[MAXN];
int path_edges[MAXN];
bool in_queue[MAXN];

bool spfa(int n, int s)
{
    fill(dista, dista + n + 1, INF);
    queue<int> q;
    dista[s] = 0;
    q.push(s);
    in_queue[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (auto [v, w] : g[u])
        {
            if (dista[v] > dista[u] + w)
            {
                dista[v] = dista[u] + w;
                path_edges[v] = path_edges[u] + 1;
                if (path_edges[v] >= n)
                {
                    return false;
                }
                if (!in_queue[v])
                {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int e = 0; e < m; e++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    if (!spfa(n, s))
    {
        cout << "NEGATIVE CYCLE\n";
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        long long answer = (dista[i] == INF ? -1 : dista[i]);
        cout << answer << (i == n ? '\n' : ' ');
    }
}
```

教学样例输入：

```text
3 3 1
1 2 2
1 3 5
3 2 -10
```

输出：

```text
0 -5 5
```

SPFA 的 FIFO 队列版本最坏 $O(nm)$，总空间 $O(n+m)$。不能把经验上表现较快当作 $O(m)$ 保证，也不能给一个统一 $O(m)$ 的期望界而不说明随机模型。非负边主线用 Dijkstra，不靠 SLF 等启发优化抵抗构造数据。

## 全图负环与差分约束

只从 s 启动检测的是源可达负环。检测全图可设超级源 0，以权 0 连向所有原点；等价地 Bellman-Ford 初始全部 $\mathrm{dist}=0$，SPFA 初始全部入队，阈值按原图 n 个点。差分约束 `x_v<=x_u+c` 对应边 u→v 权 c；全图负环表示这些上界矛盾。这是建模方向，完整约束求解器留作后续选学。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

## 扩展选读

原地 Bellman-Ford 每轮可能更快传播，但第 n 轮仍能否继续严格松弛用于负环检测，不应据此声称精确得到“恰好 k 条边”的答案。需要标记受负环影响的目标时，收集第 n 轮改进点，再沿出边传播标记；不受影响的可达点保留有限距离。


返回：[[00-图论]]。
