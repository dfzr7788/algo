前置：[[02-图的存储]]、[[01-栈队列与双端队列]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| DFS | 3/10 | 10/10 | 分量与树上处理的基础 |
| BFS | 3/10 | 10/10 | 等权最短路的基础 |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 为什么遍历要有访问状态

从每个点枚举相邻点，若无访问标记，边 `1—2` 就会让搜索不断往返。DFS 用栈保存待探索点，倾向于深入；BFS 用队列保存待扩展点，按离源点的边数分层。两者都能判断可达，只有 BFS 的首次发现距离直接保证无权最短路。

不要把遍历访问标记与回溯搜索混淆：枚举所有简单路径可能在退出时撤销标记，普通可达性遍历不撤销，否则会重复大量状态。

## DFS：连通分量

图有 `1—2,2—3,4—5`。从 1 出发访问 1、2、3 得大小 3；外层继续找未访问点，从 4 出发得到 2。只从 1 开始无法发现第二个分量。下面是显式栈的可达性 DFS，入栈即标记，保证每个点只压一次。它不模拟递归退出事件；需要后序计算时见树的遍历章。

输入无向图 `n m` 和 m 条边，输出分量数，然后每个分量大小，按最小编号启动次序。`1<=n<=200000,m<=200000`，允许孤立点、重边、自环。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
vector<int> g[MAXN];
bool seen[MAXN];

int component_size(int start)
{
    stack<int> st;
    st.push(start);
    seen[start] = true;
    int total = 0;
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        ++total;
        for (int v : g[u])
        {
            if (!seen[v])
            {
                seen[v] = true;
                st.push(v);
            }
        }
    }
    return total;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sizes;
    for (int i = 1; i <= n; i++)
    {
        if (!seen[i])
        {
            sizes.push_back(component_size(i));
        }
    }
    cout << sizes.size() << '\n';
    for (int s : sizes)
    {
        cout << s << '\n';
    }
}
```

教学样例输入：

```text
5 3
1 2
2 3
4 5
```

输出：

```text
2
3
2
```

## BFS：从最少边数推导分层

源点距离为 0，第一次发现的邻居距离为 1。队首距离为 k 时，队列里尚未处理的点距离只会是 k 或 $k+1$；因此先发现的路线不会比以后发现的路线更长。距离数组 −1 同时表示未发现和不可达，必须在入队时更新，而不是等出队再标记。

对 `1—2,1—3,2—4,3—4`，初始队列 `[1]`；扩展 1 得 `[2,3]`；扩展 2 发现 4 得 `[3,4]`；扩展 3 时 4 已被发现，无需再进队，$\mathrm{dist}[4]=2$。

输入无向图 `n m s`，随后 m 条边，输出 s 到 $1\ldots n$ 的最少边数，不可达为 −1。容量同上。parent_node 保存一条最短路径的前驱；沿目标回溯到 s 再反转即可输出路径，但不保证字典序最小。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int dista[MAXN], parent_node[MAXN];

void bfs(int n, int s)
{
    fill(dista, dista + n + 1, -1);
    queue<int> q;
    dista[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (dista[v] == -1)
            {
                dista[v] = dista[u] + 1;
                parent_node[v] = u;
                q.push(v);
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
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(n, s);
    for (int i = 1; i <= n; i++)
    {
        cout << dista[i] << (i == n ? '\n' : ' ');
    }
}
```

教学样例输入：

```text
5 4 1
1 2
1 3
2 4
3 4
```

输出：

```text
0 1 1 2 -1
```

## 正确性与复杂度

访问标记保证每点至多一次；每点处理时枚举自己的全部邻接记录，所以邻接表上 DFS、BFS 都为 $O(n+m)$ 时间、$O(n+m)$ 总空间，辅助栈或队列 $O(n)$。若改为矩阵，枚举邻居变为 $O(n^{2})$。DFS 递归深度在链上可能为 n，C++ 不保证能承受 200000 层，模板用显式栈规避。

多源 BFS 把所有源点距离设为 0 并一起入队，求到最近源的距离。网格 BFS 只生成合法邻居而不显式存边，必须检查越界与障碍。边权不等时首次到达不再保证最短，见 Dijkstra 及 0-1 BFS。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

返回：[[00-图论]]。
