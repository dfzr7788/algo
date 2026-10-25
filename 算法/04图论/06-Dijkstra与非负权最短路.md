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

## ABC463E Roads and Gates

[官方题面](https://atcoder.jp/contests/abc463/tasks/abc463_e)

道路有非负通行费，任意城市 i 到 j 还可付 X[i]+X[j]+Y 传送，求城市1到其余城市的最短路。N,M≤2×10⁵。

> [!tip]- 提示一
> 直接补齐全部传送边要 O(N²)；边权可以拆成出发点成本和到达点成本。

> [!tip]- 提示二
> 加入公共虚拟节点0，把一次传送变为两条有向边。
>
> 复习：[[04图论/06-Dijkstra与非负权最短路]]。

> [!example]- 详细题解
> **建模与源码主线。** 源码保留每条道路的两条有向记录；每个城市加 `i→0` 权 X[i]、`0→i` 权 X[i]+Y。这样只增加 2N 条边。`dis` 存最短距离，重载比较器使 priority_queue 按距离从小到大出队，用 vis 跳过重复堆项，然后遍历 head/nxt 邻接链表松弛。
>
> **正确性与适用条件。** 原传送 i→j 可替换为 i→0→j，费用完全相同；新图中虚拟点没有别的连接方式，经过0的两步也总可还原成一次传送。因此两图城市间最短路一致。全部边权非负，首次弹出的未确定城市取得最终最短距离，满足 Dijkstra 前提。
>
> **手算与边界。** X1=3、X2=4、Y=2 时，1→0→2 费用为 3+6=9；若另有费用7的道路则最短为7。Y 只应收一次，不能在两段都加。
>
> **实际复杂度与实现。** 边数 E=2M+2N，二叉堆实现时间 O((N+E) log(N+E))，有效空间 O(N+E)。源码使用固定容量链式前向星；dis 必须为 long long，且0号虚拟点也需要距离和访问标记。

## P16292 两栖作战

[官方题面](https://www.luogu.com.cn/problem/P16292)

0/1地形N×N网格从左上到右下，四邻移动，同地形不换形态、异地形换一次，最小化切换次数；N≤5000。

> [!tip]- 提示一
> 边权是相邻格是否不同，不是每走一步都花1。

> [!tip]- 提示二
> 0权松弛进双端队列头，1权松弛进尾，按非降距离推进。
>
> 复习：[[04图论/06-Dijkstra与非负权最短路]]。

> [!example]- 详细题解
> **建模与源码主线。** 源码dis起点0，其余无穷，deque初放起点。弹出(x,y)后枚举四邻，wei=[s[x][y]≠s[nx][ny]]，严格改善时更新dis；wei=0 push_front，wei=1 push_back，首次弹出终点即输出。它按松弛而非普通BFS首次入队永久标记处理。
>
> **正确性与适用条件。** 同一距离的0边应优先处理，1边只能去下一层；deque在有效处理顺序上维持距离层次，与非负最短路原理一致。所有移动代价相加恰为形态变化数，因此最短路就是最少切换，不能按路长优化。
>
> **手算与边界。** 网格两行00、11，无论选择哪条最短步数路线都需切换1次；若全0，即使移动很多步费用仍为0。可用全同地形检查把0权错误当1的实现。
>
> **实际复杂度与实现。** 顶点N²、边至多4N²，0-1 BFS时间O(N²)，空间O(N²)。源码固定s约25MB、dis约100MB，再加deque动态空间；memset覆盖整张5005²表，不能只按实际小N估计初始化开销。

返回：[[00-图论]]。
