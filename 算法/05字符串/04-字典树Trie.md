前置：[[01-字符串基础与暴力匹配]]、[[03-二叉树与搜索树]]。

## 难度与重要程度

| 算法或主题 | 难度 | 重要程度 | 理由 |
|---|---:|---:|---|
| Trie 完整词查询 | 4/10 | 8/10 | 路径存在与单词结束必须区分 |
| Trie 前缀计数 | 4/10 | 9/10 | 共用前缀路径，重复词需要累加计数 |

评分为本项目主观学习建议，尺度见 [[00-字符串]]。


## 为什么词典需要前缀树

有 n 个词、多次询问“有多少词以 app 开头”。逐个检查最坏需要扫描整个词典；Trie 把共同前缀共享在同一条树路径中，查询只走 app 的三条字符边。精确单词查询也能用 set、unordered_map；Trie 的主要优势是同时保留前缀层次，而不是声称所有词典任务它都最快。

根代表空前缀，边上的字符决定路径，节点编号不是字符编码。`app` 与 `apple` 的开头共用 a→p→p；`app` 末节点虽然还有孩子，也可以是完整词末尾，必须用 end_count 标记。

## 两种计数各保存什么

- $\mathrm{pass\_count}[u]$：插入词中以根到 u 的路径为前缀的数量，重复词按重复次数计入；根的 pass 是词的总数。
- $\mathrm{end\_count}[u]$：恰好在 u 结束的词数量。只有路径存在不能表示该词真的被插入。
- $\mathrm{child}[u][k]$：从节点 u 沿第 k 种字符到的节点；0 表示不存在。根也是编号 0，但从不作为新建孩子，实际节点 $1\ldots \mathrm{nodes}$，因此不会混淆。

词 `app,apple,app,apt`：路径 app 的 $\mathrm{pass}=3$、$end=2$；路径 ap 的 $\mathrm{pass}=4$、$end=0$；apple 的 $\mathrm{pass}=end=1$。查询 app 的完整次数是 2，前缀数量是 3，查询 ap 的完整次数为 0。

## 操作过程与容量

insert_word 从根走每个字符，缺孩子才新建，每个到达节点 pass 加 1，末节点 end 加 1。find_node 只走路径，缺边返回 −1；查询函数按语义取对应计数。重复插入不再新建节点，只增加计数。

节点数不超过“总插入字符数+1”，不是“单词数+1”。本模板总插入长度 $\le 200000$，26 列数组本身约 20.8 MB，加计数约 1.6 MB；按 4 字节 int 估算。字符集扩大到 62 时空间乘以 62，不能不算内存直接照抄。

## 完整教学模板

输入 t 组数据；每组 `n q`，n 个非空小写词，然后 q 行 `type word`，$\mathrm{type}=1$ 问完整词次数，$\mathrm{type}=2$ 问前缀数量。每组 $n,q\le 200000$、总插入长度 $\le 200000$、总查询长度 $\le 200000$，字符仅 a..z；重复词计重复次数。例子使用单组，但程序明确支持清理多测。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 200000 + 5;
int child[MAXNODE][26], pass_count[MAXNODE], end_count[MAXNODE];
int nodes = 0;

void insert_word(const string &word)
{
    int u = 0;
    ++pass_count[u];
    for (char c : word)
    {
        int k = c - 'a';
        if (child[u][k] == 0)
        {
            child[u][k] = ++nodes;
        }
        u = child[u][k];
        ++pass_count[u];
    }
    ++end_count[u];
}

int find_node(const string &word)
{
    int u = 0;
    for (char c : word)
    {
        int k = c - 'a';
        if (child[u][k] == 0)
        {
            return -1;
        }
        u = child[u][k];
    }
    return u;
}

int count_exact(const string &word)
{
    int u = find_node(word);
    return (u == -1 ? 0 : end_count[u]);
}

int count_prefix(const string &prefix)
{
    int u = find_node(prefix);
    return (u == -1 ? 0 : pass_count[u]);
}

void clear_trie()
{
    for (int u = 0; u <= nodes; u++)
    {
        fill(child[u], child[u] + 26, 0);
        pass_count[u] = 0;
        end_count[u] = 0;
    }
    nodes = 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        clear_trie();
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++)
        {
            string word;
            cin >> word;
            insert_word(word);
        }
        while (q--)
        {
            int type;
            string word;
            cin >> type >> word;
            cout << (type == 1 ? count_exact(word) : count_prefix(word)) << '\n';
        }
    }
}
```

教学样例输入（自编）：

```text
1
4 5
app
apple
app
apt
1 app
2 app
1 ap
2 ap
2 b
```

输出：

```text
2
3
0
4
0
```

## 正确性与复杂度

每次插入恰好使它经过的前缀节点 pass 增 1，使其终止节点 end 增 1，所以不变量对每次操作成立。长度 L 的插入、精确查询、前缀查询都是 $O(L)$，固定字符集数组边查找为 $O(1)$；并不是所有“字典树实现”都无条件 $O(L)$，若换成有序映射需计每步查边成本。

设插入总长度 S、查询总长度 Q、有效节点 V、字符集 $\sigma$，含清理的总时间 $O(S+Q+\sigma V)$，空间 $O(\sigma V)$，固定数组实际分配 $\mathrm{MAXNODE}\times 26$；$\sigma =26$ 时可写 $O(S+Q)$、$O(S)$。clear_trie 先清旧 nodes 范围，再设 $\mathrm{nodes}=0$，不能先归零而只清根。内存清理也要含 end、pass。

## 原有特殊字符应用与平台区别

原笔记的数字、`#`、`-` 共 12 种字符用于差分序列编码，已完整迁入字符串建模题解章，保留 `[3,6,50,10]→3#44#-40#` 的思路和对应实现。它不是本篇 26 字母模板，不能把 `'-'−'a'` 当作合法列号。

[洛谷 P8306 — Trie](https://www.luogu.com.cn/problem/P8306) 同模型为多测前缀计数，但字符为大小写字母和数字，共 62 种，总输入长度可到 $3\times 10^{6}$；本模板容量和字符映射不同，不能直接提交。 [洛谷 P2580 — 错误的点名](https://www.luogu.com.cn/problem/P2580) 需完整姓名查找、另记是否已点名，不能用 pass 代替 end，也不是简单输出插入次数。


## 练习与复盘

先手算正文样例，再运行并检查最小输入、重复字符与边界；分层题目见 [[10-字符串题单]]，独立建模见 [[11-字符串综合练习]]。

## 扩展选读：删除

删除一次已存在单词时，沿路径让 pass 减 1、末端 end 减 1。先验证 $end>0$，否则会减出负数。若只减计数而不移除节点，路径存在已经不能说明前缀仍有活跃单词，必须检查 $\mathrm{pass}>0$。删除、回收空间与 01-Trie 按需后学，本轮主模板只提供插入和查询。

## ABC475E Quiz Competition Qualifiers

[官方题面](https://atcoder.jp/contests/abc475/tasks/abc475_e)

N 人答 K 道二选一题，每题按当前未定者答对人数是否超出剩余名额，决定一批晋级或淘汰；每次翻转某人的一题答案后，询问此人是否晋级。N≤30000,K≤200,Q≤50000。

> [!tip]- 提示一
> 把答案转换成相对标准答案的0/1串，同一未定群体共享一个正确性前缀。

> [!tip]- 提示二
> Trie 节点的人数可直接给出这一群体在下一题的答对人数；已经晋级的人数要单独累计。
>
> 复习：[[05字符串/04-字典树Trie]]。

> [!example]- 详细题解
> **建模与源码主线。** `iscor[i][k]` 存答对位，insert_path 沿位串增加 counts，remove 先减去旧路径，再翻转并插入新路径。询问沿该人的路径走，qnum 是已确定晋级人数，c 是当前节点1分支人数。若 qnum+c≤M，则当前所有1分支晋级；被问者为1就立即 Yes，为0则 qnum+=c 并进入0分支。若超出容量，0分支全部淘汰，只有1分支继续。
>
> **正确性与适用条件。** 每一步的 Trie 节点恰好表示题目规则中的未定人群，两种判断与官方过程逐字对应。问题不是取字典序最大的恰好 M 人：最后仍未定的人全部淘汰，可能不足 M 人；因此走完 K 位而未提前确定晋级时必须 No。
>
> **手算与边界。** M=1，两人的正确性串都为1：第一题答对人数2超额，没人被确定晋级；题目结束两人均淘汰。把它误作任选一名最高分选手会得出错误结果。
>
> **实际复杂度与实现。** 建树 O(NK)，每次删除、插入和判断均 O(K)，总 O((N+Q)K)。旧节点不回收，节点数上界随新增路径增长为 O((N+Q)K)，不是只算 NK；源码预留16000005个节点，trie与counts约192MB，另需正确性表和字符串。

返回：[[00-字符串]]。
