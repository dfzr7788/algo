前置：[[03-DFS与BFS]]、[[04-堆与优先级队列]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| 堆优化 Dijkstra | 5/10 | 10/10 | 非负权稀疏图的主力最短路 |
| 0-1 BFS | 5/10 | 7/10 | 利用两种权值省掉堆的对数因子 |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 为什么普通 BFS 不够

边 `1→2` 权为 10，`1→3` 权为 1，`3→2` 权为 1。BFS 会先找到一条边到 2，但代价 10 比两条边的代价 2 大。我们要比较的是累计权值，而不是边数。

Dijkstra 保存 $\mathrm{dist}[v]$ 为目前已发现路线的最小代价，每次取暂定距离最小的未确定点 u。边权非负时，绕经其他尚未确定点再到 u 不会更短，因此 u 的距离可以确定，再更新它的邻居。负权边会破坏这个贪心前提。

## 堆记录与手算

初始堆 `(0,1)`；取 1 后产生 `(10,2),(1,3)`；取 3 后把 $\mathrm{dist}[2]$ 改成 2，再插入 `(2,2)`。旧记录 `(10,2)` 仍在堆里，必须用 `cost!=dist[u]` 跳过，否则重复扩展浪费时间。不能在入堆时永久标记，因为第一次入堆的 10 还会改进。

这里采用懒删除，不手写 decrease-key。每次成功松弛插入新记录；无向图需要读边后添加两条有向记录。

## 完整 Dijkstra 模板

输入有向图 `n m s`，m 行 `u v w`，输出距离，不可达 −1。`n,m<=200000,0<=w<=10^9`，点 $1\ldots n$，允许重边和零权。最短简单路径不超过 `(n−1)10^9`，long long 与 `2^60` 哨兵足够，$\mathrm{cost}+w$ 不会溢出。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const long long INF = (1LL << 60);
vector<pair<int, long long>> g[MAXN];
long long dista[MAXN];

void dijkstra(int n, int s)
{
    fill(dista, dista + n + 1, INF);
    priority_queue<pair<long long, int>,
        vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dista[s] = 0;
    pq.push({0, s});
    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();
        if (cost != dista[u])
        {
            continue;
        }
        for (auto [v, w] : g[u])
        {
            if (dista[v] > cost + w)
            {
                dista[v] = cost + w;
                pq.push({dista[v], v});
            }
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    dijkstra(n, s);
    for (int i = 1; i <= n; i++)
    {
        long long answer = (dista[i] == INF ? -1 : dista[i]);
        cout << answer << (i == n ? '\n' : ' ');
    }
}
```

教学样例输入：

```text
4 3 1
1 2 10
1 3 1
3 2 1
```

输出：

```text
0 2 1 -1
```

## 正确性与复杂度

若有效出堆的最小暂定点 u 仍有更短路线，沿该路线找第一个未确定点 x，它前驱已确定并已松弛 x；非负的后续边使 $\mathrm{dist}[x]$ 不超过该更短路线总代价，于是应比 u 更早被取出，矛盾。有效扩展每点最多一次。

此懒删除版本至多 $O(m)$ 次插入，时间 $O(n+m \log (m+2))$，总空间 $O(n+m)$，堆可占 $O(m)$。对通常无重边或多项式数量重边的图，常写 $O((n+m) \log n)$，但允许任意大量平行边时 $\log m$ 更精确。稠密图用扫描最小 dist 的朴素版本可达 $O(n^{2}+m)$，不一定需要堆。

## 0-1 BFS：双端队列模拟两档优先级

边权只有 0 或 1 时，队首当前距离为 d，下一批候选只需区分 d 与 $d+1$。零权松弛放队首，单位权放队尾，因此无需通用堆。仍需比较并更新距离，不能直接照搬“首次发现就不再修改”的普通 BFS。

例：`1→2(1),1→3(0),3→2(0)`，先入队的 2 距离为 1，随后 3 从队首取出将 2 改为 0，并把 2 再放队首。done 在出队时设置，重复旧记录跳过。首次有效出队按最短距离顺序，之后不再需要扩展。

输入输出同上，但 w 只能为 0 或 1；$n,m\le 200000$。最短距离至多 $n-1$，可以用 int。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const int INF = 1000000000;
vector<pair<int, int>> g[MAXN];
int dista[MAXN];
bool done[MAXN];

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    fill(dista, dista + n + 1, INF);
    deque<int> q;
    dista[s] = 0;
    q.push_front(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        if (done[u])
        {
            continue;
        }
        done[u] = true;
        for (auto [v, w] : g[u])
        {
            if (dista[v] > dista[u] + w)
            {
                dista[v] = dista[u] + w;
                if (w == 0)
                {
                    q.push_front(v);
                }
                else
                {
                    q.push_back(v);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int answer = (dista[i] == INF ? -1 : dista[i]);
        cout << answer << (i == n ? '\n' : ' ');
    }
}
```

教学样例输入：

```text
4 3 1
1 2 1
1 3 0
3 2 0
```

输出：

```text
0 0 0 -1
```

每点有效扩展一次，每条出边扫描一次，插入不超过成功松弛次数，所以时间 $O(n+m)$，总空间 $O(n+m)$。多测清理 g、dista、done；把权值 2 也按尾插会破坏两档顺序。恢复路径可在成功松弛时记录 parent；只在 dist 相等时不更新，可避免零权环导致前驱来回变化。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

返回：[[00-图论]]。
