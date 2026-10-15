前置：[[13-树的遍历与子树信息]]、[[11-倍增思想]]。

## 难度与重要程度

| 算法或主题  |   难度 | 重要程度 | 理由             |
| ------ | ---: | ---: | -------------- |
| 倍增 LCA | 6/10 | 9/10 | 树上多次祖先和路径查询的基础 |
| 树上距离公式 | 4/10 | 9/10 | 在公共祖先处分解唯一通路   |

评分为本项目的主观学习建议，口径见 [[00-图论]]。


## 公共祖先能省下什么

有根树中 u、v 向根走，两条路最先汇合的点就是最近公共祖先 LCA，也就是所有公共祖先中深度最大的点。每次逐步上爬在长链中要 $O(n)$，q 次可能 $O(nq)$。倍增预处理让一次跨过 1、2、4、8… 层，单次 $O(\log n)$。

u 本身可以是 v 的祖先，$LCA(u,u)=u$；LCA 随根变化，树上无权距离不随根变化。不要把 LCA 和直径中点混为一谈。

## 倍增状态与两个查询阶段

$up[u][j]$ 是 u 向上 $2^{j}$ 步的祖先，`up[u][j]=up[up[u][j−1]][j−1]`。不存在的祖先设 0，0 行始终为 0；深度根为 0。$LOG=19$ 保存 $j=0\ldots 18$，足够表示 $n\le 200000$ 的深度差，换容量时要同步调整 LOG。

先把较深点提升到相同深度。若已经同点，就得到 LCA。否则从大到小看跳跃：只有两点的 $2^{j}$ 祖先不同才一起跳，这样还停留在 LCA 下面；最后各自父亲就是 LCA。若一开始不对齐深度，祖先比较没有相同层含义。

## 手算

边 `1—2,1—3,2—4,2—5,3—6`，根 1。查询 4、5：深度相同，大步祖先相同不能跳，父亲同为 2，答案 2。查询 4、6：父亲分别 2、3，不同，可以一起跳一层，此时父亲同为 1，答案 1。查询 2、4：先把 4 提升一层到 2，直接返回。

无权距离为 `depth[u]+depth[v]−2depth[lca]`，因为两条根路径共享的根到 LCA 段被算了两次。带权树用根路径权值和 dist_root 替代 depth，但深度仍按边数用于提升；树上唯一简单路径的权值公式即使带负边也成立，和“允许重复行走的最短路”含义不同。

## 完整模板

输入 `n q root`，$n-1$ 条无向边保证为树，然后 q 对点。`n,q<=200000`，输出每次查询 `LCA 无权距离`。build 的 order 保证父亲倍增表先完成，避免递归；up 的 0 行由全局初始化保证。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const int LOG = 19;
vector<int> g[MAXN];
int up[MAXN][LOG], depth_node[MAXN];

void build(int root)
{
    vector<int> order = {root};
    for (int index = 0; index < (int)order.size(); index++)
    {
        int u = order[index];
        for (int j = 1; j < LOG; j++)
        {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
        for (int v : g[u])
        {
            if (v != up[u][0])
            {
                up[v][0] = u;
                depth_node[v] = depth_node[u] + 1;
                order.push_back(v);
            }
        }
    }
}

int lca(int u, int v)
{
    if (depth_node[u] < depth_node[v])
    {
        swap(u, v);
    }
    int difference = depth_node[u] - depth_node[v];
    for (int j = 0; j < LOG; j++)
    {
        if ((difference >> j) & 1)
        {
            u = up[u][j];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int main()
{
    int n, q, root;
    cin >> n >> q >> root;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build(root);
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        int ancestor = lca(u, v);
        int distance = depth_node[u] + depth_node[v] - 2 * depth_node[ancestor];
        cout << ancestor << ' ' << distance << '\n';
    }
}
```

教学样例输入：

```text
6 4 1
1 2
1 3
2 4
2 5
3 6
4 5
4 6
2 4
3 3
```

输出：

```text
2 2
1 4
2 1
3 0
```

## 正确性、复杂度与边界

倍增递推把同一个跳跃拆成两段，归纳得到 $2^{j}$ 祖先。相同深度时，若当前两点的某层祖先不同，这些祖先仍严格在 LCA 之下；跳完最大可行步后两点父亲相同且就是最近公共祖先。预处理 $O(n \log n)$，每次查询 $O(\log n)$，总空间 $O(n \log n)$。

单点、同点、祖先关系、根参与查询都应覆盖。森林不能直接按一棵树建表；需要先标分量，不同树的 LCA 无定义。本模板也不支持动态插删边。多测清理 g、up、depth。

## 原有链接：隐式树应用

[AtCoder ABC465 D — X to Y](https://atcoder.jp/contests/abc465/tasks/abc465_d) 已核对官方题面：非负整数 x 与 $\operatorname{floor}(x/K)$ 相连，要求两整数间最少操作，X、Y 可到 $10^{18}$。它适合把整数视作隐式树、爬父亲找汇合点；0 的自跳转不改善距离。不能显式建出所有整数点，也不是上面 n 点、q 次查询的直接倍增模板题。


## 练习与复盘

先手算正文样例，再修改边界自行验证；分层平台题见 [[20-图论题单]]，综合建模见 [[21-图论综合练习]]。

## 扩展选读

欧拉遍历序列上的深度最小值可转成 RMQ 求 LCA；Tarjan 离线 LCA 用并查集；路径最大边、k 级祖先可以附加倍增信息。树链剖分、动态树属于后续选学，未在本章给完整实现。


返回：[[00-图论]]。
